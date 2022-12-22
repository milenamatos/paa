#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int size, first_position;
  int *array;
} originalList;

typedef struct
{
  int value, array_index;
} item;

typedef struct
{
  item *items;
} heapType;

void minHeapify(heapType *A, int i, int size)
{
  int esq = (i * 2) + 1, dir = (i * 2) + 2, maior;
  item troca;

  if (esq < size && A->items[esq].value <= A->items[i].value)
    maior = esq;
  else
    maior = i;
  if (dir < size && A->items[dir].value <= A->items[maior].value) // maior por i
    maior = dir;

  if (maior != i)
  {
    troca = A->items[maior];
    A->items[maior] = A->items[i];
    A->items[i] = troca;
    minHeapify(A, maior, size);
  }
}

void buildMinHeap(heapType *heap, int size)
{
  int i;
  for (i = size / 2; i >= 0; i--)
    minHeapify(heap, i, size);
}

void maxHeapify(heapType *heap, int i, int size)
{
  int esq = (i * 2) + 1, dir = (i * 2) + 2, maior;
  item troca;

  if (esq < size && heap->items[esq].value > heap->items[i].value)
    maior = esq;
  else
    maior = i;
  if (dir < size && heap->items[dir].value > heap->items[maior].value)
    maior = dir;

  if (maior != i)
  {
    troca = heap->items[maior];
    heap->items[maior] = heap->items[i];
    heap->items[i] = troca;
    maxHeapify(heap, maior, size);
  }
}

void buildMaxHeap(heapType *heap, int size)
{
  int i;
  for (i = size / 2; i >= 0; i--)
    maxHeapify(heap, i, size);
}

void heapSort(heapType *heap, int size)
{

  int i, heapSize = size;
  item aux;
  buildMaxHeap(heap, size);
  for (i = size - 1; i >= 1; i--)
  {
    aux = heap->items[0];
    heap->items[0] = heap->items[i];
    heap->items[i] = aux;
    heapSize--;
    maxHeapify(heap, 0, heapSize);
  }
}

int main()
{
  item *items;
  originalList *array_list;
  int n_arrays, iterations, i;

  scanf("%d", &n_arrays);
  scanf("%d", &iterations);

  items = (item *)malloc(sizeof(item) * n_arrays);
  array_list = (originalList *)malloc(sizeof(originalList) * n_arrays);

  int j, current_index = 0, total_length = 0, arr_length;
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

    items = (item *)realloc(items, sizeof(item) * total_length);

    int k;
    for (k = 0; k < arr_length; k++)
    {
      int value;
      scanf("%d", &value);

      items[current_index].value = value;
      items[current_index].array_index = j;
      current_index++;

      array_list[j].array[k] = value;
    }
  }

  heapType heap;
  heap.items = items;

  buildMinHeap(&heap, total_length);

  heapSort(&heap, total_length);

  int sum = 0;
  if (iterations > 1)
  {
    for (i = 0; i < iterations; i++)
    {
      item removed_item = heap.items[i];
      int index = removed_item.array_index;
      array_list[index].size--;
      array_list[index].first_position++;
    }
  }

  for (i = 0; i < n_arrays; i++)
  {
    originalList item = array_list[i];
    if (item.size == 0)
      continue;
    sum += item.array[item.first_position];
  }

  printf("%d", sum);

  return 1;
}