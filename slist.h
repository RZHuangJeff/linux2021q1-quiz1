#ifndef QUIZ1_SLIST_H
#define QUIZ1_SLIST_H

/*
 * Structure of node_t
 */
typedef struct __node {
  int value;
  struct __node *next;
} node_t;

/*
 * Attempt to make a new node contains value v,
 * and add it to the head of list.
 */
node_t *list_make_node_t(node_t *list, int v);

/*
 * Attemp to free the storage used by list.
 */
void list_free(node_t **list);

/*
 * Sort the elements of list in acensing order.
 */
void quicksort(node_t **list);

/* 
 * Sort the elements of list in acensing order,
 * with none recursive quicksort.
 */
void nr_quicksort(node_t **list);

#endif // QUIZ1_SLIST_H