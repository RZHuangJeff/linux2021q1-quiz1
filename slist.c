#include "slist.h"

#include <stddef.h>
#include <stdlib.h>

static inline void list_add_node_t(node_t **list, node_t *node_t);
static inline void list_concat(node_t **left, node_t *right);

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

static inline void list_add_node_t(node_t **list, node_t *node_t) {
  node_t->next = *list;
  *list = node_t;
}

static inline void list_concat(node_t **left, node_t *right) {
  while (*left)
    left = &((*left)->next);

  *left = right;
}