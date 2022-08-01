#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE 1000000

typedef struct
{
    int size, current_i;
    int *array;
} item;

void execute(item *arrays, int n_arrays, int i)
{
    int counter = 0, sum = 0;
    while (counter < i)
    {
        int execute_sum = (counter == i - 1) ? 1 : 0;
        int j, smallest_pos;
        double smallest = MAX_VALUE;

        for (j = 0; j < n_arrays; j++)
        {
            item curr_item = arrays[j];

            if (curr_item.size == 0)
                continue;

            int *curr_arr = arrays[j].array;
            int value = curr_arr[curr_item.current_i];

            if(value < smallest) {
                smallest = value;
                smallest_pos = j;
            }

            if (execute_sum == 1)
            {
                sum += value;
            }
        }

        arrays[smallest_pos].size--;
        arrays[smallest_pos].current_i++;

        counter++;
    }

    printf("%d", sum);
}

int main()
{
    item *arrays;
    int n_arrays, i;

    scanf("%d", &n_arrays);
    scanf("%d", &i);

    arrays = (item *)malloc(sizeof(item) * n_arrays);

    int j, arr_length;
    for (j = 0; j < n_arrays; j++)
    {
        scanf("%d", &arr_length);

        if (arr_length == 0) continue;

        arrays[j].size = arr_length;
        arrays[j].current_i = 0;
        arrays[j].array = (int *)malloc(sizeof(int) * arr_length);

        int k;
        for (k = 0; k < arr_length; k++)
        {
            scanf("%d", &arrays[j].array[k]);
        }
    }

    execute(arrays, n_arrays, i);

    return 0;
}