#include <stdio.h>
#include <stdlib.h>

long long int size = 0;

long long int *convert(long long int val)
{
  long long int i = 0, j, k = 0;
  long long int *arr = (long long int *) malloc(100 * sizeof(long long int));
  do
  {
    arr[i] = val % 2;
    val = val / 2;
    i++;
    if (i % 100 == 0 && val > 0)
      arr = (long long int *) realloc(arr, 100 * sizeof(long long int));
  } while (val > 0);

  long long int *final_arr = (long long int *) malloc(i * 2 * sizeof(long long int));
  for (j = i - 1; j >= 0; j--)
  {
    final_arr[k] = arr[j];
    k++;
  }
  size = i;
  return final_arr;
}

void adjust(long long int *arr)
{
  long long int i;
  arr = (long long int *) realloc(arr, size * sizeof(long long int));
  size++;
  for (i = size - 1; i > 0; i--)
  {
    arr[i] = arr[i - 1];
  }
  arr[0] = 1;
}

void sum_one(long long int *arr)
{
  long long int n = size - 1;
  if (arr[n] == 0)
  {
    arr[n] = 1;
  }
  else
  {
    arr[n] = 0;
    n--;
    do
    {
      if (arr[n] == 0)
      {
        arr[n] = 1;
        break;
      }
      else
      {
        arr[n] = 0;
        n--;
        if (n < 0)
        {
          adjust(arr);
          break;
        }
      }
    } while (n >= 0);
  }

}

long long int count_ones(long long int *arr)
{
  long long int i, count = 0;
  for (i = 0; i < size; i++)
  {
    if (arr[i] == 1)
      count++;
  }
  return count;
}

int main()
{
  long long int a, b, i, count = 0;

  scanf("%lld", &a);
  scanf("%lld", &b);

  long long int *arr = convert(a);

  long long int n = b - a;

  count += count_ones(arr);

  for (i = 0; i < n; i++)
  {
    sum_one(arr);
    count += count_ones(arr);
  }

  printf("%lld", count);

  return 1;
}