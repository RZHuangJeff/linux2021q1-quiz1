#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "list.h"

#include "common.h"

#define MAX_LEVEL 300

static uint16_t values[20480];

static void list_qsort(struct list_head *head)
{
    struct list_head list_less, list_greater;
    struct listitem *pivot;
    struct listitem *item = NULL, *is = NULL;

    if (list_empty(head) || list_is_singular(head))
        return;

    INIT_LIST_HEAD(&list_less);
    INIT_LIST_HEAD(&list_greater);

    pivot = list_first_entry(head, struct listitem, list);
    list_del(&pivot->list);

    list_for_each_entry_safe (item, is, head, list) {
        if (cmpint(&item->i, &pivot->i) < 0)
            list_move_tail(&item->list, &list_less);
        else
            list_move(&item->list, &list_greater);
    }

    list_qsort(&list_less);
    list_qsort(&list_greater);

    list_add(&pivot->list, head);
    list_splice(&list_less, head);
    list_splice_tail(&list_greater, head);
}

static void list_nr_qsort(struct list_head *head)
{
    if (list_empty(head) || list_is_singular(head))
        return;
    
    struct list_head *beg[MAX_LEVEL], *end[MAX_LEVEL], *item, *safe, *swap;
    struct listitem *pivot, *it;
    int i = 0, lcnt, rcnt;

    beg[0] = head;
    end[0] = head;
    while (i >= 0) {
        if (beg[i]->next != end[i] && beg[i]->next->next != end[i]) {
            pivot = list_entry(beg[i]->next, struct listitem, list);

            lcnt = rcnt = 0;
            for (item = pivot->list.next, safe = item->next; item != end[i]; item = safe, safe = item->next) {
                if (cmpint(&list_entry(item, struct listitem, list)->i, &pivot->i) < 0) {
                    list_move_tail(item, &pivot->list);
                    lcnt++;
                } else {
                    list_move(item, &pivot->list);
                    rcnt++;
                }
            }

            end[i + 1] = end[i];
            beg[i + 1] = end[i] = &pivot->list;
            i++;

            if (lcnt < rcnt) {
                swap = beg[i]; beg[i] = beg[i - 1]; beg[i - 1] = swap;
                swap = end[i]; end[i] = end[i - 1]; end[i - 1] = swap;
            }
        } else {
            i--;
        }
    }
}

int main(void)
{
    struct list_head testlist, testlist_nr;
    struct listitem *item, *is = NULL;
    size_t i, j;
    clock_t beg, end;

    random_shuffle_array(values, (uint16_t) ARRAY_SIZE(values));

    INIT_LIST_HEAD(&testlist);
    INIT_LIST_HEAD(&testlist_nr);

    assert(list_empty(&testlist));
    assert(list_empty(&testlist_nr));

    for (i = 0; i < ARRAY_SIZE(values); i++) {
        item = (struct listitem *) malloc(sizeof(*item));
        assert(item);
        item->i = values[i];
        list_add_tail(&item->list, &testlist);

        item = (struct listitem *) malloc(sizeof(*item));
        assert(item);
        item->i = values[i];
        list_add_tail(&item->list, &testlist_nr);
    }

    assert(!list_empty(&testlist));
    assert(!list_empty(&testlist_nr));

    qsort(values, ARRAY_SIZE(values), sizeof(values[0]), cmpint);

    beg = clock();
    list_qsort(&testlist);
    end = clock();
    printf("Recursive:\t%lfs\n", (end - beg)/(double)CLOCKS_PER_SEC);

    beg = clock();
    list_nr_qsort(&testlist_nr);
    end = clock();
    printf("Non-recursive:\t%lfs\n", (end - beg)/(double)CLOCKS_PER_SEC);

    i = j = 0;
    list_for_each_entry_safe (item, is, &testlist, list) {
        assert(item->i == values[i]);
        list_del(&item->list);
        free(item);
        i++;
    }

    list_for_each_entry_safe (item, is, &testlist_nr, list) {
        assert(item->i == values[j]);
        list_del(&item->list);
        free(item);
        j++;
    }

    assert(i == ARRAY_SIZE(values));
    assert(j == ARRAY_SIZE(values));
    assert(list_empty(&testlist));
    assert(list_empty(&testlist_nr));

    return 0;
}
