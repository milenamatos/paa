#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct
{
  int exist;
  int visited;
} position;

int full_count = 0;

void count(position arr[MAX][MAX], int n, int i, int j)
{
  if (arr[i][j].visited == 1)
  {
    return;
  }

  if (arr[i][j].exist == 0)
    full_count++;

  arr[i][j].visited = 1;

  if (i > 0)
  {
    if (j > 1)
      count(arr, n, i - 1, j - 2);
    else if (j + 2 < MAX)
      count(arr, n, i - 1, j + 2);
  }

  if (i > 1)
  {
    if (j > 0)
      count(arr, n, i - 2, j - 1);
    else if (j + 1 < MAX)
      count(arr, n, i - 2, j + 1);
  }

  if (i + 1 < n)
  {
    if (j > 1)
      count(arr, n, i + 1, j - 2);
    else if (j + 2 < MAX)
      count(arr, n, i + 1, j + 2);
  }

  if (i + 2 < n)
  {
    if (j > 0)
      count(arr, n, i + 2, j - 1);
    else if (j + 1 < MAX)
      count(arr, n, i + 2, j + 1);
  }
}

int main()
{
  int n, i, j;
  position arr[MAX][MAX];

  scanf("%d", &n);

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < MAX; j++)
    {
      arr[i][j].exist = 0;
      arr[i][j].visited = 0;
    }
  }

  for (i = 0; i < n; i++)
  {
    int exist, dont_exist;
    scanf("%d", &dont_exist);
    scanf("%d", &exist);

    for (j = dont_exist; j < dont_exist + exist; j++)
    {
      arr[i][j].exist = 1;
    }
  }

  count(arr, n, 0, 0);

  printf("%d", full_count);
}