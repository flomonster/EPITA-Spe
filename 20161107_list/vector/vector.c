# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include "vector.h"

/*
 * vector_make(capacity) create an empty vector
 * with initial storage size capacity
 */
struct vector* vector_make(size_t capacity)
{
  struct vector *v = malloc(sizeof(struct vector));
  v->capacity = capacity;
  v->size = 0;
  v->data = malloc(sizeof(int) * capacity);
  for (size_t i = 0; i < capacity; i++)
    v->data[i] = 0;
  return v;
}
 
/*
 * vector_push_back(vect, x) add x at the end of vect
 * if vect is full increase capacity
 */
void vector_push_back(struct vector *vect, int x)
{
  if (vect->size == vect->capacity)
  {
    int *tmp = 
      realloc(vect->data, (size_t) (1.61 * vect->capacity * sizeof (int)));
    if (tmp == NULL) 
    {
      warn("realloc of data fails");
      return;
    }
    vect->data = tmp;
    vect->capacity *= 1.61;
  }
  vect->data[vect->size] = x;
  vect->size++;
}
 
/*
 * vector_pop_back(vect, &x) get the last element of vect
 * remove the element
 * store result in x
 * return true (!=0) if size > 0
 * return false (0) otherwise
 */
int  vector_pop_back(struct vector *vect, int *x)
{
  if (vect->size == 0)
    return 0;
  *x = vect->data[vect->size - 1];
  vect->size--;
  return 1;
}
 
/*
 * vector_push_front(vect, x) add x at the beginning of vect
 * if vect is full increase capacity
 */
void vector_push_front(struct vector *vect, int x)
{
  if (vect->size == vect->capacity)
  {
    int *tmp = 
      realloc(vect->data, (size_t) (1.61 * vect->capacity * sizeof (int)));
    if (tmp == NULL) 
    {
      warn("realloc of data fails");
      return;
    }
    vect->data = tmp;
    vect->capacity *= 1.61;
  }
  for (size_t i = 1; i < vect->size; i++)
    vect->data[i] = vect->data[i-1];
  vect->data[0] = x;
  vect->size++;
}
 
/*
 * vector_pop_back(vect, &x) get the first element of vect
 * remove the element
 * store result in x
 * return true (!=0) if size > 0
 * return false (0) otherwise
 */
int  vector_pop_front(struct vector *vect, int *x)
{
  if (vect->size == 0)
    return 0;
  *x = vect->data[0];
  for (size_t i = 0; i < vect->size - 1; i++)
    vect->data[i] = vect->data[i+1];
  vect->data[vect->size - 1] = 0;
  vect->size--;
  return 1;
}
 
/*
 * vector_insert_at(vect, pos, x) add x in pos cell of vect
 * return true (!=0) if pos <= size of vect
 * return false (0) otherwise
 * vector_insert_at(v, v->size, x) is equivalent to vector_push_back(v, x)
 * vector_insert_at(v, 0, x) is equivalent to vector_push_front(v, x)
 * if vect is full increase capacity
 */
int vector_insert_at(struct vector *vect, size_t pos, int x)
{
  if (vect->size == vect->capacity)
  {
    int *tmp = 
      realloc(vect->data, (size_t) (1.61 * vect->capacity * sizeof (int)));
    if (tmp == NULL) 
    {
      warn("realloc of data fails");
      return 0;
    }
    vect->data = tmp;
    vect->capacity *= 1.61;
  }

  if (pos > vect->size)
    return 0;
  for (size_t i = pos + 1; i < vect->size + 1; i++)
    vect->data[i] = vect->data[i-1];
  vect->data[pos] = x;
  vect->size++;
  return 1;
}
 
/*
 * vector_extract_at(vect, pos, &x) get the pos element of vect
 * remove the element
 * store result in x
 * return false (0) if size == 0 or pos >= size
 * vector_extract_at(v, v->size - 1, &x) is equivalent to vector_pop_back(v, &x)
 * vector_extract_at(v, 0, &x) is equivalent to vector_pop_front(v, &x)
 */
int vector_extract_at(struct vector *vect, size_t pos, int *x)
{
  if (vect->size == 0 || pos >= vect->size)
    return 0;
  *x = vect->data[pos];
  for (size_t i = pos; i < vect->size - 1; i++)
    vect->data[i] = vect->data[i+1];
  vect->data[vect->size - 1] = 0;
  vect->size--;
  return 1;
}
 
/*
 * vector_clone(vect) create a complete copy of vect
 * both storage contains the same elements but are not at the same memory place
 */
struct vector* vector_clone(struct vector *vect)
{
  struct vector *v = malloc(sizeof(struct vector));
  v->capacity = vect->capacity;
  v->size = vect->size;
  v->data = malloc(sizeof(int) * v->capacity);
  for (size_t i = 0; i < v->capacity; i++)
    v->data[i] = vect->data[i];
  return v;
}
