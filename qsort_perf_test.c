#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "slist.h"
#include "prng.h"

static bool is_ordered(node_t *list) {
    if (!list)
        return false;

    int value = list->value;
    for (node_t *n = list; n; n = n->next) {
        if (n->value < value)
            return false;
    }

    return true;
}

static void init_lists(node_t **la, node_t **lb, int cnt) {
    prng_set_seed(prng_gen_number());

    int val;
    while (cnt--) {
        val = prng_gen_number();

        *la = list_make_node_t(*la, val);
        *lb = list_make_node_t(*lb, val);
    }
}

int main() {
    node_t *lista = NULL;
    node_t *listb = NULL;

    const int listlen[] = {1 << 5, 1 << 10, 1 << 20};    
    int size, round = 3;

    clock_t beg, end;
    for (int i = 0; i < round; i++) {
        size = listlen[i];
        init_lists(&lista, &listb, size);

        printf("Round %d Size = %7d\n", i, size);

        beg = clock();
        quicksort(&lista);
        end = clock();

        printf("Recursive:\t%lfs\tPASS: %s\n", (end - beg)/(double)CLOCKS_PER_SEC, is_ordered(lista) ? "TRUE": "FALSE");

        beg = clock();
        nr_quicksort(&listb);
        end = clock();

        printf("Non-recursive:\t%lfs\tPASS: %s\n", (end - beg)/(double)CLOCKS_PER_SEC, is_ordered(listb) ? "TRUE": "FALSE");
    
        list_free(&lista);
        list_free(&listb);
    }

    return 0;
}