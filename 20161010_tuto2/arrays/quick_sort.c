 
# include <stdlib.h>
 
# include "helper.h"
# include "quick_sort.h"
 
int* partition(int *begin, int *end)
{
  int *pivot = begin + (end - begin) / 2;
  int pval = *pivot;
  swap(pivot, end);
  pivot = begin;
  for (int *i = begin; i < end; i += 1)
  {
    if (*i < pval)
    {
      swap(pivot, i);
      pivot += 1;
    }
  }
  swap(pivot, end);
  return pivot;
}
 
void quick_sort(int *begin, int *end)
{
  int *pivot;
  if (end - begin > 1)
  {
    pivot = partition(begin, end);
    quick_sort(begin, pivot - 1);
    quick_sort(pivot + 1, end);
  }
}
 
void hybrid_sort(int *begin, int *end)
{
  if (end - begin < 2 || array_is_sorted(begin, end))
    return;
  quick_sort(begin, end);
}
