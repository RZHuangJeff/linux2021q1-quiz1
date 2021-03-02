#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "slist.h"
#include "prng.h"

static bool list_is_ordered(node_t *list) {
  bool first = true;
  int value;
  while (list) {
    if (first) {
      value = list->value;
      first = false;
    } else {
      if (list->value < value)
        return false;
      value = list->value;
    }
    list = list->next;
  }
  return true;
}

static void list_display(node_t *list) {
  printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
  while (list) {
    printf("%d ", list->value);
    list = list->next;
  }
  printf("\n");
}

int main(int argc, char **argv) {
  size_t count = 20;

  prng_set_seed(time(NULL));

  node_t *list = NULL;
  while (count--)
    list = list_make_node_t(list, prng_gen_number() % 1024);

  list_display(list);
  quicksort(&list);
  list_display(list);

  if (!list_is_ordered(list))
    return EXIT_FAILURE;

  list_free(&list);
  return EXIT_SUCCESS;
}