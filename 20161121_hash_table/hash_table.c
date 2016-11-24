/* hash_table.c */
/* Hash Table implementation: header */
 
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include "hash_table.h"
 
/*
* hash(data):
* compute the hash of the nul terminated string data.
*/
uint32_t hash(char *data)
{
  uint32_t h = 0;
  size_t i = 0;
  while (*(data + i))
  {
    h += *(data + i);
    h += h * 1024;
    h = h ^ (h / 64);
    i++;
  }
  h += h * 8;
  h = h ^ (h / 2048);
  h += h * 32768;
  return h;
}

/*
* create_htable(capacity):
* build a new hash table with initial capacity.
*/
struct htable *create_htable (size_t capacity )
{
  struct htable *ht = malloc(sizeof (struct htable));
  ht->size = 0;
  ht->capacity = capacity;
  ht->tab = malloc(sizeof(struct pair) * capacity);
  for (size_t i = 0; i < capacity; i++)
    ht->tab[i] = NULL;
  return ht;
}
 
/*
* access_htable(htable, key):
* returns a pointer to the pair containing the given key
*/
struct pair *access_htable (struct htable *htable , char *key)
{
  uint32_t h = hash(key);
  size_t pos = h % htable->capacity;
  if (!htable->tab[pos])
    return NULL;
  struct pair *p = htable->tab[pos];
  while (p)
  {
    if (p->hkey == h && !strcmp(p->key, key))
      return p;
    p = p->next;
  }
  return NULL;
}

/*
* auto_resize(htable)
* check and resize if the htable is too full
*/
void auto_resize(struct htable *htable)
{
  if ((float) htable->size / (float) htable->capacity > .75)
  {
    struct htable old = *htable;
    struct htable *new = create_htable(old.capacity * 2);
    *htable = *new;
    free(new);
    for (size_t i = 0; i < old.capacity; i++)
      if (old.tab[i])
      {
        struct pair *p = old.tab[i];
        struct pair *swap;
        while (p)
        {
          swap = p;
          p = p->next;
          add_htable(htable, swap->key, swap->value);
          free(swap);
        }
      }
    free(old.tab);
  }
}
 
/*
* add_htable(htable,key,value):
* add the pair (key,value) to the hash table
*/
int add_htable (struct htable *htable , char *key, void *value)
{
  uint32_t h = hash(key);
  size_t pos = h % htable->capacity;
  if (htable->tab[pos])
  {
    struct pair *p = htable->tab[pos];
    while (p->next)
    {
      if (p->hkey == h && !strcmp(p->key, key))
        return 0;
      p = p->next;
    }
    if (p->hkey == h && !strcmp(p->key, key))
      return 0;
  }
  htable->size++;
  struct pair *p = malloc(sizeof (struct pair));
  p->hkey = h;
  p->key = key;
  p->value = value;
  p->next = htable->tab[pos];
  htable->tab[pos] = p;
  auto_resize(htable);
  return 1;
}


/*
* remove_htable(htable, key):
* removes the pair containing the given key from the hash table
*/
void remove_htable (struct htable *htable , char *key)
{
  uint32_t h = hash(key);
  size_t pos = h % htable->capacity;
  if (!htable->tab[pos])
    return;
  struct pair *p = htable->tab[pos];
  if (p->hkey == h && !strcmp(p->key, key))
  {
    htable->tab[pos] = p->next;
    free(p);
    htable->size--;
    return;
  }
  while (p->next)
  {
    if (p->next->hkey == h && !strcmp(p->next->key, key))
    {
      struct pair *swap = p->next;
      p->next = swap->next;
      free(swap);
      htable->size--;
      return;
    }
    p = p->next;
  }
}
 
/*
* clear_htable(htable):
* delete all pairs in the table
*/
void clear_htable (struct htable *htable)
{
  htable->size = 0;
  for (size_t i = 0; i < htable->capacity; i++)
    if (htable->tab[i])
    {
      struct pair *p = htable->tab[i];
      htable->tab[i] = NULL;
      while (p)
      {
        struct pair *swap = p;
        p = p->next;
        free(swap);
      }
    }
}
