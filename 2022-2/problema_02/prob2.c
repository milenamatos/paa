// Nome: Milena de Matos Siqueira, RA: 122044

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int size, first_position;
  int *array;
} item;

typedef struct
{
  int value, original_index;
} array_item;

void merge(array_item *array_list, int low, int medium, int high)
{
  int i, j, k;
  int n1 = medium - low + 1;
  int n2 = high - medium;

  array_item temp1[n1], temp2[n2];

  for (i = 0; i < n1; i++)
    temp1[i] = array_list[low + i];
  for (j = 0; j < n2; j++)
    temp2[j] = array_list[medium + 1 + j];

  i = 0;
  j = 0;
  k = low;

  while (i < n1 && j < n2)
  {
    if (temp1[i].value < temp2[j].value || (temp1[i].value == temp2[j].value && temp1[i].original_index < temp2[j].original_index))
    {
      array_list[k] = temp1[i];
      i++;
    }
    else
    {
      array_list[k] = temp2[j];
      j++;
    }
    k++;
  }

  while (i < n1)
  {
    array_list[k] = temp1[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    array_list[k] = temp2[j];
    j++;
    k++;
  }
}

void merge_sort(array_item *array_list, int low, int high)
{
  if (low < high)
  {
    int medium = low + (high - low) / 2;

    merge_sort(array_list, low, medium);
    merge_sort(array_list, medium + 1, high);

    merge(array_list, low, medium, high);
  }
}

void execute(array_item *sorted_array, item *array_list, int n_arrays, int iterations)
{
  int sum = 0, i, arrays_count = n_arrays;

  if (iterations > 1)
  {
    for (i = 0; i < iterations - 1; i++)
    {
      int removed_index = sorted_array[i].original_index;
      array_list[removed_index].size--;
      array_list[removed_index].first_position++;
    }
  }

  for (i = 0; i < arrays_count; i++)
  {
    item item = array_list[i];
    if (item.size == 0)
      continue;

    sum += item.array[item.first_position];
  }

  printf("%d", sum);
}

int main()
{
  item *array_list;
  array_item *sorted_array;
  int n_arrays, iterations;

  scanf("%d", &n_arrays);
  scanf("%d", &iterations);

  array_list = (item *)malloc(sizeof(item) * n_arrays);
  sorted_array = (array_item *)malloc(sizeof(array_item) * n_arrays);

  int j, arr_length, total_length = 0, index = 0;
  for (j = 0; j < n_arrays; j++)
  {
    scanf("%d", &arr_length);

    if (arr_length == 0)
    {
      n_arrays--;
      j--;
      continue;
    }

    array_list[j].size = arr_length;
    array_list[j].first_position = 0;
    array_list[j].array = (int *)malloc(sizeof(int) * arr_length);

    total_length += arr_length;
    sorted_array = (array_item *)realloc(sorted_array, sizeof(array_item) * total_length);

    int k;
    for (k = 0; k < arr_length; k++)
    {
      scanf("%d", &array_list[j].array[k]);

      sorted_array[index].value = array_list[j].array[k];
      sorted_array[index].original_index = j;
      index++;
    }
  }

  merge_sort(sorted_array, 0, total_length - 1);

  execute(sorted_array, array_list, n_arrays, iterations);

  return 0;
}