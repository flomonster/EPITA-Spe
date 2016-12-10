# define _DEFAULT_SOURCE
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>


struct chunk {
  struct chunk *next, *prev;
  size_t        size;
  long          free;
  void         *data;
};

typedef struct chunk chunk;

static inline
size_t word_align(size_t n)
{
  return (n + 7) & ~7;
}

/* zerofill(ptr, len): write len 0 bytes at the address ptr */
void zerofill(void *ptr, size_t len)
{
  for (size_t i = 0; i < len / sizeof (size_t); i++)
    ((size_t *) ptr)[i] = 0;
}

/* wordcpy(dst, src, len) copy len bytes from src to dst */
void wordcpy(void *dst, void *src, size_t len)
{
  for (size_t i = 0; i < len / sizeof (size_t); i++)
    ((size_t *) dst)[i] = ((size_t *) src)[i];
}

static
struct chunk* get_base(void) 
{
  static struct chunk *base = NULL;
  if (!base) 
  {
    base = sbrk(sizeof (chunk));
    base->next = NULL;
    base->prev = NULL;
    base->data = NULL;
    base->size = 0;
    base->free = 0;
  }
  return base;
}

/*
 * extend_heap(last, size) extends the heap with a new chunk containing a data 
 * block of size bytes.
 * Return 1 in case of success, and return 0 if sbrk(2) fails.
 */
static
int extend_heap(struct chunk *last, size_t size)
{
  chunk *new = sbrk(sizeof (chunk) + size);
  if (new == (void *) - 1)
    return 0;
  last->next = new;
  new->prev = last;
  new->next = NULL;
  new->size = size;
  new->data = new + 1;
  new->free = 0;
  return 1;
}

static
void split(chunk *c, size_t size)
{
  chunk *new = c->data + size;

  new->next = c->next;
  new->prev = c;
  new->data = new + 1;
  new->size = c->size - size - sizeof (chunk);
  
  c->next = new;
  c->size = size;

  free(new->data);
}

static
void merge(chunk *c)
{
  c->size += c->next->size + sizeof (chunk);
  c->next = c->next->next;
  if (c->next)
    c->next->prev = c;
}

static
struct chunk* find_chunk(size_t size)
{
  chunk *base = get_base();
  while (base->next)
  {
    if (base->next->free && base->next->size >= size)
    {
      if (base->next->size - size > sizeof (chunk) + size / 4)
        split(base->next, size);
      return base;
    }
    base = base->next;
  }
  return base;
}

static
struct chunk* get_chunk(void *p)
{
  if (!p || (chunk *) p < get_base() || p > sbrk(0) ||
      ((size_t) p & 7))
    return NULL;
  chunk *c = p;
  c--;
  if (c->data != p)
    return NULL;
  return c;
}

void* malloc(size_t size)
{
  if (!size)
    return NULL;
  size = word_align(size);
  chunk *c = find_chunk(size);
  if (!c->next && !extend_heap(c, size))
      return NULL;
  c = c->next;
  c->free = 0;
  return c->data;
}

void* calloc(size_t nb, size_t size)
{
  size_t mul;
  if (__builtin_mul_overflow(nb, size, &mul))
    return NULL;
  void *c = malloc(mul);
  if (!c)
    return NULL;
  zerofill(c, mul);
  return c;
}

void* realloc(void *old, size_t newsize)
{
  if (!newsize)
  {
    free(old);
    return NULL;
  }

  if (!old)
    return malloc(newsize);

  chunk *c = get_chunk(old);
  if (!c)
    return NULL;
  if (c->size >= newsize)
    return old;
  void *new = malloc(newsize);
  if (!new)
    return NULL;
  wordcpy(new, old, c->size);
  c->free = 1;
  return new;
}

void free(void *p)
{
  chunk *c = get_chunk(p);
  if (c)
  {
    c->free = 1;
    if (c->next && c->next->free)
      merge(c);
    if (c->prev->free)
      merge(c->prev);
  }
}
