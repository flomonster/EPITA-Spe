/* hash_table.h */
/* Hash Table implementation: header */
 
# ifndef _HASH_TABLE_H_
# define _HASH_TABLE_H_
 
# include <stdint.h>
# include <stdlib.h>
 
struct pair {
  uint32_t hkey ;
  char *key;
  void *value;
  struct pair *next;
};
 
struct htable {
  size_t size , capacity ;
  struct pair **tab;
};
 
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
  uint32_t pos = hash(key) % htable->capacity;
  if (!htable->tab[pos])
    return NULL;

  
}
 
/*
* add_htable(htable,key,value):
* add the pair (key,value) to the hash table
*/
int add_htable (struct htable *htable , char *key, void *value);
 
/*
* remove_htable(htable, key):
* removes the pair containing the given key from the hash table
*/
void remove_htable (struct htable *htable , char *key);
 
/*
* clear_htable(htable):
* delete all pairs in the table
*/
void clear_htable (struct htable *htable );
 
# endif /* _HASH_TABLE_H_ */
