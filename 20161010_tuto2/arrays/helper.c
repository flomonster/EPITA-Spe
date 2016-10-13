/* helper's functions */
 
# define _XOPEN_SOURCE 500
 
# include <assert.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
 
# include "helper.h"
 
/* swap(a,b): swap memory location content */
void swap(int *a, int *b)
{
  int s = *a;
  *a = *b;
  *b = s;
}
 
/* array_print(begin, end) print integer array */
/* with a fixed padding of 4 chars             */
void array_print(int *begin, int *end)
{
  int line = 0;
  for (; begin != end; ++begin) {
    if (line > 72) {
      printf("|`|\n");
      line = 0;
    }
    line += printf("| %4d ", *begin);
  }
  printf("|\n");
}
 
/* array_is_sorted(begin, end): test if array is sorted */
int array_is_sorted(int *begin, int *end)
{
  for (int *i = begin; i < end; i ++)
  {
    if (*i > *(i + 1))
      return 0;
  }
  return 1;
}
 
/* array_sorted_fill(begin, end) */
void array_sorted_fill(int *begin, int *end)
{
  for (int i = 0; begin != end; ++begin, ++i)
    *begin = i;
}
 
/* array_random_fill(begin, end) */
void array_random_fill(int *begin, int *end)
{
  for (; begin != end; ++begin)
    *begin = random() % 10000;
}
 
 
void bench_sort(int *begin, int *end, sort_fun sort, const char *msg)
{
  struct timespec t0, t1;
 
  clock_gettime(CLOCK_MONOTONIC, &t0);
  sort(begin, end);
  clock_gettime(CLOCK_MONOTONIC, &t1);
  printf("%s:    \t%g\n", msg, time_gdiff(t0, t1));
  assert(array_is_sorted(begin, end));
}
