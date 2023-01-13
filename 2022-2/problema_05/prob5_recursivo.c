// Nome: Milena de Matos Siqueira, RA: 122044
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int min(int val1, int val2)
{
  return (val1 < val2) ? val1 : val2;
}

int get_min_cost(int c, int antennas[], int table_points[], int i, int sum)
{
  if (i >= c - 1) {
    return sum;
  }

  if (table_points[i] == 0) {
    return get_min_cost(c, antennas, table_points, i + 1, sum);
  }

  int antenna1_sum = antennas[0] + get_min_cost(c, antennas, table_points, i + antennas[0] + 1, sum);

  int antenna2_sum = antennas[1] + get_min_cost(c, antennas, table_points, i + antennas[1] + 1, sum);

  return min(antenna1_sum, antenna2_sum);
}

int main()
{
  int i, n, c, t1, t2;

  scanf("%d %d %d %d", &n, &c, &t1, &t2);

  int points[n];
  int table_points[c+1];

  for (i = 0; i < c; i++)
  {
    table_points[i] = 0;
  }

  for (i = 0; i < n; i++)
  {
    scanf("%d", &points[i]);
    table_points[points[i]] = 1;
  }

  int antennas[2] = {t1, t2};

  int start_index = points[0];

  int result = get_min_cost(c, antennas, table_points, start_index, 0);
  printf("%d", result);

  return 0;
}