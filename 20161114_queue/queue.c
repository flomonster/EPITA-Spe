# include <stdlib.h> 
# include <stdio.h> 
# include "queue.h"

/*
 * queue_init(queue) initialize an empty queue container
 * allocation of the container is kept external for more flexibility
 */
void queue_init(struct queue *queue)
{
  queue->size = 0;
  queue->store = NULL;
}
 
/*
 * queue_is_empty(queue) test for emptyness
 */
int queue_is_empty(struct queue *queue)
{
  return !queue->size;
}
 
/*
 * queue_push(queue, elm) push elm
 */
void queue_push(struct queue *queue, void *elm)
{
  struct list *l = malloc(sizeof (struct list));
  l->data = elm;
  l->next = NULL;
  if (queue_is_empty(queue))
    queue->store = l;
  else
  {
    struct list *p = queue->store;
    for (size_t i = 0; i < queue->size - 1; i++)
      p = p->next;
    p->next = l;
  }
  queue->size++;
}
 
/*
 * queue_pop(queue) pop the next element (FIFO order)
 * returns NULL if the queue is empty
 */
void* queue_pop(struct queue *queue)
{
  if (!queue->size)
    return NULL;
  queue->size--;
  struct list *l = queue->store;
  void *elm = l->data;
  queue->store = l->next;
  free(l);
  return elm;
}
