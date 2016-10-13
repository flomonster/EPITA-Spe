# include <stdio.h>
# include <stdlib.h>
# include <err.h>

// insert using the naive algo
void array_insert(int *begin, int *end, int x)
{
  int *i = end;
  while (i >= begin && x < *i)
  {
    *(i + 1) = *i;
    i--;
  }
  *(i + 1) = x;
}
 
int *bin_search(int *begin, int *end, int x)
{
  int *left = begin, *right = end, *mid;
  while (left <= right)
  {
    mid = (right - left) / 2 + left;
    if (*mid == x)
      return mid;
    if (*mid > x)
      right = mid - 1;
    else
      left = mid + 1;
  }
  for (int *i = begin; i <= end; i += 1)
    printf("%d ", *i);
  printf(":> %d / %d  / %d\n", x, *left, *right);
  return left;
}


// insert using binary search
void array_insert_bin(int *begin, int *end, int x)
{
  int *i = bin_search(begin, end, x);
  int *e = end + 1;
  while (e > i)
  {
    *e = *(e - 1);
    e -= 1;
  }
  *i = x;
}

// insertion sort using naive method
void array_insert_sort(int *begin, int *end)
{
  for (int *i = begin; i < end; i += 1)
  {
    array_insert(begin, i, *(i + 1));
  }
}
 
// insertion sort using binary search
void array_insert_sort_bin(int *begin, int *end)
{
  for (int *i = begin; i < end; i += 1)
  {
    array_insert_bin(begin, i, *(i + 1));
  }
}
