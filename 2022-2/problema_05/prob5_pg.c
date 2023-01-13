// Nome: Milena de Matos Siqueira, RA: 122044
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long *table_points, *antennas, c;

long min(long val1, long val2)
{
  return (val1 < val2) ? val1 : val2;
}

long get_min_cost()
{
  long i, j, n = 2;
  long result[n + 1][c + 2];

  for (i = 1; i < n + 1; i++)
  {
    for (j = 0; j <= c + 1; j++)
      result[i][j] = 0;
  }

  for (i = 0; i <= n; i++)
  {
    for (j = c; j >= 0; j--)
    {
      if (i == 0)
      {
        result[i][j] = INT_MAX;
      }
      else if (table_points[j] == 0)
      {
        result[i][j] = result[i][j + 1];
      }
      else
      {
        long res = (j + antennas[i - 1] + 1 <= c)
                      ? result[i][j + antennas[i - 1] + 1]
                      : 0;

        result[i][j] = min(
            antennas[i - 1] + res,
            result[i - 1][j]);
      }
    }
  }

  return result[n][0];
}

int main()
{
  int i, n;
  long t1, t2;
  scanf("%d", &n);
  scanf("%ld", &c);
  scanf("%ld", &t1);
  scanf("%ld", &t2);

  table_points = (long *)malloc(sizeof(long) * (c + 1));

  for (i = 0; i <= c; i++)
  {
    table_points[i] = 0;
  }

  for (i = 0; i < n; i++)
  {
    long point;
    scanf("%ld", &point);
    table_points[point] = 1;
  }

  antennas = (long *)malloc(sizeof(long) * 2);
  antennas[0] = t1;
  antennas[1] = t2;

  long result = get_min_cost();
  printf("%ld", result);

  free(table_points);
  free(antennas);

  return 0;
}