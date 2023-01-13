// Nome: Milena de Matos Siqueira, RA: 122044
#include <stdio.h>
#include <stdlib.h>

int *table_points, *dp_table, *antennas, c;

int min(int val1, int val2)
{
  return (val1 < val2) ? val1 : val2;
}

int get_min_cost(int i)
{
  if (i > c)
  {
    return 0;
  }

  if (dp_table[i] != -1)
  {
    return dp_table[i];
  }

  if (table_points[i] == 0)
  {
    dp_table[i] = get_min_cost(i + 1);
    return dp_table[i];
  }

  int antenna1_sum = antennas[0] + get_min_cost(i + antennas[0] + 1);

  int antenna2_sum = antennas[1] + get_min_cost(i + antennas[1] + 1);

  int min_value = min(antenna1_sum, antenna2_sum);
  // dp_table[i] = min_value;

  return min_value;
}

int main()
{
  int i, n, t1, t2;
  scanf("%d", &n);
  scanf("%d", &c);
  scanf("%d", &t1);
  scanf("%d", &t2);

  table_points = (int *)malloc(sizeof(int) * (c + 1));

  for (i = 0; i <= c; i++)
  {
    table_points[i] = 0;
  }

  for (i = 0; i < n; i++)
  {
    int point;
    scanf("%d", &point);
    table_points[point] = 1;
  }

  antennas = (int *)malloc(sizeof(int) * 2);
  antennas[0] = t1;
  antennas[1] = t2;

  dp_table = (int *)malloc(sizeof(int) * (c + 1));
  for (i = 0; i <= c; i++)
    dp_table[i] = -1;

  int result = get_min_cost(0);
  printf("%d", result);

  free(table_points);
  free(antennas);
  free(dp_table);

  return 0;
}