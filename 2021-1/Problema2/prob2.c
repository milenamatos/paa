#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int max_sum(int arr[], int quantity, int max_bytes)
{
  int max_sum = 0;
  int i, j;

  for (i = 0; i < quantity; i++)
  {
    for (j = i + 1; j < quantity; j++)
    {
      int sum = arr[i] + arr[j];
      if (sum > max_sum)
      {
        if (sum <= max_bytes)
        {
          max_sum = sum;
          if (sum == max_bytes)
          {
            break;
          }
        } else {
          break;
        }
      }
    }
  }

  return max_sum;
}

void merge(int arr[], int low, int medium, int high)
{
  int i, j, k;
  int n1 = medium - low + 1;
  int n2 = high - medium;

  int temp1[n1], temp2[n2];

  for (i = 0; i < n1; i++)
    temp1[i] = arr[low + i];
  for (j = 0; j < n2; j++)
    temp2[j] = arr[medium + 1 + j];

  i = 0;
  j = 0;
  k = low;

  while (i < n1 && j < n2)
  {
    if (temp1[i] <= temp2[j])
    {
      arr[k] = temp1[i];
      i++;
    }
    else
    {
      arr[k] = temp2[j];
      j++;
    }
    k++;
  }

  while (i < n1)
  {
    arr[k] = temp1[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    arr[k] = temp2[j];
    j++;
    k++;
  }
}

void merge_sort(int arr[], int low, int high)
{
  if (low < high)
  {
    int medium = low + (high - low) / 2;

    merge_sort(arr, low, medium);
    merge_sort(arr, medium + 1, high);

    merge(arr, low, medium, high);
  }
}

int main()
{
  int quantity_files;
  int arr_files[MAX];
  int max_bytes;

  scanf("%d", &quantity_files);
  scanf("%d", &max_bytes);

  int i;
  for (i = 0; i < quantity_files; i++)
  {
    scanf("%d", &arr_files[i]);
  }

  merge_sort(arr_files, 0, quantity_files - 1);

  if (arr_files[0] + arr_files[1] > max_bytes)
  {
    printf("NONE\n");
  }
  else
  {
    int max = max_sum(arr_files, quantity_files, max_bytes);
    if (max == 0)
    {
      printf("NONE\n");
    }
    else
    {
      printf("%d\n", max);
    }
  }
  return 1;
}