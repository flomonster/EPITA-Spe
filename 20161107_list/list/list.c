# include <stdlib.h> 
# include <stdio.h> 
# include "list.h" 
/*
 * Standard operations
 * We're working with sentinels and external allocation
 * This means that our lists always have a fake head (the sentinel)
 * and all allocations (and free) are performed by the caller, not the operation
 */
 
/*
 * list_init(list)
 * initialise the sentinel node list
 */
void list_init(struct list *list)
{
  list->next = NULL;
}
 
/*
 * list_is_empty(list)
 * returns true if the list is empty
 * remember, we have a sentinel thus a list always has at least one node,
 * the list is empty if this node doesn't have a next.
 */
int list_is_empty(struct list *list)
{
  return list->next == NULL;
}

/*
 * list_len(list)
 * returns the length of the list (don't count the sentinel)
 */
size_t list_len(struct list *list)
{
  size_t length = 0;
  struct list *save = list;
  while (list->next)
  {
    length++;
    list = list->next;
  }
  list = save;
  return length;
}
 
/*
 * list_push_front(list, elm)
 * attach elm in front of list, that is after the sentinel.
 * Note that elm is already a node, you just have to attach it.
 */
void list_push_front(struct list *list, struct list *elm)
{
  elm->next = list->next;
  list->next = elm;
}
 
/*
 * list_pop_front(list)
 * Extract the first element (not the sentinel) of list.
 * This operation detaches the element from the list and returns it (caller is
 * responsible for freeing it.)
 * If the list is empty, the function returns NULL.
 */
struct list* list_pop_front(struct list *list)
{
  if (list_is_empty(list))
    return NULL;
  struct list *front = list->next;
  list->next = list->next->next;
  return front; 
}
 
/*
 * list_find(list, value)
 * search for the first node containing value and returns (without detaching it)
 * the corresponding list node. The function returns NULL if the value is not
 * present in the list.
 */
struct list* list_find(struct list *list, int value)
{
  struct list *save = list;
  while (list->next)
  {
    if (list->next->data == value)
    {
      struct list *node = list->next;
      list = save;
      return node; 
    }
    list = list->next;
  }
  list = save;
  return NULL;
}
 
/*
 * list_is_sorted(list)
 * check whether the list is sorted in increasing order
 */
int list_is_sorted(struct list *list)
{
  struct list *save = list;
  list = list->next;
  while (list->next && list->data <= list->next->data)
    list = list->next;
  int b = list->next == NULL;
  list = save;
  return b;
}
 
/*
 * list_insert(list, elm)
 * insert elm in the sorted list (keeping the list sorted)
 * Like list_push_front, elm is already a list node.
 */
void list_insert(struct list *list, struct list *elm)
{
  struct list *save = list;
  while (list->next && list->next->data < elm->data)
    list = list->next;
  list_push_front(list, elm);
  list = save;  
}
 
/*
 * More algorithms
 */
 
/*
 * list_rev(list)
 * reverse the list using the same nodes (just move them) and the same sentinel.
 */
void list_rev(struct list *list)
{
  struct list *sentinel = list;
  struct list *save = NULL;
  while (list->next)
  {
    struct list *swap = list->next;
    list->next = save;
    save = list;
    list = swap;
  }
  list->next = save;
  sentinel->next = list;
  list = sentinel;
}
 
/*
 * list_half_split(list, second)
 * split the list in half and put the second half in second
 * second is an empty list (just a sentinel)
 */
void list_half_split(struct list *list, struct list *second)
{
  struct list *save = list;
  size_t i = 0;
  while (list->next)
  {
    i++;
    if (i)
      second->next = list;
    list = list->next;
  }
  list = second->next;
  second->next = list->next;
  list->next = NULL;
  list = save;
}

void print_list(struct list *list)
{
  int line = 1;
  printf("[");
  if (list->next) {
    goto pastfst;
    while (list->next) {
      line += printf(";");
      if (line > 72) {
	printf("\n ");
	line = 1;
      }
      pastfst:
      line += printf(" %d", list->next->data);
      list = list->next;
    }
  }
  printf(" ]\n");
}
