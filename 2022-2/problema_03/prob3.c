// Nome: Milena de Matos Siqueira, RA: 122044

#include <stdio.h>
#include <stdlib.h>

int *columns, *columns_fixed, *columns_used;

void print_solution(int *columns, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%d ", columns[i] + 1);
  }
  printf("\n");
}

int construct_candidates(int *columns_used, int n, int candidates[])
{
  int i, n_candidates = 0;
  for (i = 0; i < n; i++)
  {
    if (columns_used[i] == -1)
    {
      candidates[n_candidates] = i;
      n_candidates++;
    }
  }

  return n_candidates;
}

void backtracking(int *columns, int *columns_used, int k, int n)
{
  if (k == n - 1)
  {
    print_solution(columns, n);
    return;
  }

  k++;
  int candidates[n];
  int n_candidates = construct_candidates(columns_used, n, candidates);

  for (int i = 0; i < n_candidates; i++)
  {
    int item = candidates[i];

    if (columns_fixed[k] != -1 && columns_fixed[k] != item)
    {
      // não é valido pois não corresponde aos guaritas fixos
      continue;
    }

    columns[k] = item;
    columns_used[item] = 1;

    backtracking(columns, columns_used, k, n);

    columns_used[item] = -1;
  }
}

void init_arrays(int n)
{
  int i, j;

  columns = (int *)malloc(sizeof(int) * n);
  columns_fixed = (int *)malloc(sizeof(int) * n);
  columns_used = (int *)malloc(sizeof(int) * n);

  for (i = 0; i < n; i++)
  {
    columns[i] = -1;
    columns_fixed[i] = -1;
    columns_used[i] = -1;
  }
}

int main()
{
  int i, n, m;

  scanf("%d", &n);
  scanf("%d", &m);

  init_arrays(n);

  for (i = 0; i < m; i++)
  {
    int x, y;
    scanf("%d", &x);
    scanf("%d", &y);

    columns_fixed[y - 1] = x - 1;
  }

  backtracking(columns, columns_used, -1, n);

  return 0;
}