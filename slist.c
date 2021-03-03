#include "slist.h"

#include <stddef.h>
#include <stdlib.h>

#define MAX_COUNT 300

static inline void list_add_node_t(node_t **list, node_t *node_t);
static inline void list_concat(node_t **left, node_t *right);

static node_t *list_find_tail(node_t *list);

node_t *list_make_node_t(node_t *list, int value) {
  node_t *nnode;
  if (!(nnode = malloc(sizeof(node_t))))
    return list;

  nnode->value = value;
  nnode->next = list;

  return nnode;
}

void list_free(node_t **list) {
  if (!list)
    return;

  for (node_t *tmp = *list; tmp; tmp = *list) {
    *list = (*list)->next;
    free(tmp);
  }

  *list = NULL;
}

void quicksort(node_t **list) {
  if (!*list)
    return;

  node_t *pivot = *list;
  int value = pivot->value;
  node_t *p = pivot->next;
  pivot->next = NULL;

  node_t *left = NULL, *right = NULL;
  while (p) {
    node_t *n = p;
    p = p->next;
    list_add_node_t(n->value > value ? &right : &left, n);
  }

  quicksort(&left);
  quicksort(&right);

  node_t *result = NULL;
  list_concat(&result, left);
  list_concat(&result, pivot);
  list_concat(&result, right);
  *list = result;
}

void nr_quicksort(node_t **list) {
    node_t **begin[MAX_COUNT], **end[MAX_COUNT], **swap;
    node_t *pivot, *ptr, **rt, **lt;
    int value, i = 0, lcnt, rcnt;

    begin[0] = list;
    end[0] = &list_find_tail(*list)->next;

    while (i >= 0) {
      if (*end[i] != *begin[i] && *end[i] != (*begin[i])->next) {
        pivot = *begin[i];
        value = pivot->value;

        ptr = (*begin[i])->next;
        rt = &pivot->next;
        lt = begin[i];

        lcnt = rcnt = 0;
        while (ptr != *end[i]) {
          if (ptr->value > value) {
            *rt = ptr;
            rt = &ptr->next;
            rcnt++;
          } else {
            *lt = ptr;
            lt = &ptr->next;
            lcnt++;
          }

          ptr = ptr->next;
        }

        *rt = *end[i];
        *lt = pivot;

        end[i + 1] = rt;
        end[i] = lt;
        begin[i + 1] = &pivot->next;
        i++;
      
        if (lcnt < rcnt) {
          swap = begin[i]; begin[i] = begin[i - 1]; begin[i - 1] = swap;
          swap = end[i]; end[i] = end[i - 1]; end[i - 1] = swap;
        }
      } else {
        i--;
      }
    }
}

static inline void list_add_node_t(node_t **list, node_t *node_t) {
  node_t->next = *list;
  *list = node_t;
}

static inline void list_concat(node_t **left, node_t *right) {
  while (*left)
    left = &((*left)->next);

  *left = right;
}

static node_t *list_find_tail(node_t *list) {
    if (!list)
        return NULL;

    node_t *tail;
    for (tail = list; tail->next; tail = tail->next);

    return tail;
}