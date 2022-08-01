#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE 1000000

typedef struct
{
    int value, arrays_pos;
} item_aux;

typedef struct
{
    int size, current_i;
    int *array;
} item;

void swap(item_aux arr[], int i, int j)
{
    item_aux temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(item_aux arr[], int p, int r)
{
    int media = (p + r) / 2;

    int index = 0;
    if (arr[p].value < arr[media].value)
    {
        if (arr[media].value < arr[r].value)
            index = media;
        else
        {
            if (arr[p].value < arr[r].value)
                index = r;
            else
                index = p;
        }
    }
    else
    {
        if (arr[r].value < arr[media].value)
            index = media;
        else
        {
            if (arr[r].value < arr[p].value)
                index = r;
            else
                index = p;
        }
    }

    swap(arr, index, r);

    // quick sort
    int x = arr[r].value;
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (arr[j].value <= x)
        {
            i++;
            swap(arr, i, j);
        }
    }

    swap(arr, i + 1, r);
    return (i + 1);
}

void quick_sort(item_aux arr[], int p, int r)
{
    if (p < r)
    {
        int q = partition(arr, p, r);
        quick_sort(arr, p, q - 1);
        quick_sort(arr, q + 1, r);
    }
}

int execute(item *arrays, int n_arrays, int i, item_aux sorted_array[], int sorted_arr_length)
{
    int counter = 0, pos = 0;

    while (counter < i - 1)
    {
        if (pos >= sorted_arr_length)
        {
            int aux_pos = 0;
            for (int j = 0; j < n_arrays; j++)
            {
                item curr_item = arrays[j];
                if (curr_item.size == 0)
                    continue;

                int value = curr_item.array[curr_item.current_i];
                sorted_array[aux_pos].arrays_pos = j;
                sorted_array[aux_pos].value = value;
                aux_pos++;

                arrays[j].current_i++;
                arrays[j].size--;
            }

            pos = 0;
            sorted_arr_length = aux_pos;
            quick_sort(sorted_array, 0, sorted_arr_length - 1);
        }

        int curr_item_pos = sorted_array[pos].arrays_pos;

        item curr_item = arrays[curr_item_pos];
        if (curr_item.size == 0)
        {
            pos++;
            continue;
        }

        int curr_value = curr_item.array[curr_item.current_i];

        arrays[curr_item_pos].current_i++;
        arrays[curr_item_pos].size--;

        sorted_array[pos].value = curr_value;

        if (curr_value >= sorted_array[pos + 1].value)
            pos++;

        counter++;
    }

    double sum = 0;
    for (int j = 0; j < sorted_arr_length; j++)
    {
        sum += sorted_array[j].value;
    }

    return sum;
}

int main()
{
    item *arrays;
    int n_arrays, i;

    scanf("%d", &n_arrays);
    scanf("%d", &i);

    arrays = (item *)malloc(sizeof(item) * n_arrays);

    item_aux *sorted_array = (item_aux *)malloc(sizeof(item_aux) * n_arrays);

    int j, arr_length, sorted_arr_pos = 0;
    for (j = 0; j < n_arrays; j++)
    {
        scanf("%d", &arr_length);

        if (arr_length == 0)
        {
            continue;
        }

        arrays[j].size = arr_length - 1;
        arrays[j].current_i = 1;
        arrays[j].array = (int *)malloc(sizeof(int) * arr_length);

        int k;
        for (k = 0; k < arr_length; k++)
        {
            int value;
            scanf("%d", &value);
            arrays[j].array[k] = value;

            if (k == 0)
            {
                sorted_array[sorted_arr_pos].value = value;
                sorted_array[sorted_arr_pos].arrays_pos = j;
                sorted_arr_pos++;
            }
        }
    }

    quick_sort(sorted_array, 0, sorted_arr_pos - 1);

    int sum = execute(arrays, n_arrays, i, sorted_array, sorted_arr_pos);
    printf("%d", sum);

    return 0;
}