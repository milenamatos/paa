#include <stdio.h>
#include <stdlib.h>

#define SIZE 1025

typedef struct
{
  int value, x, y;
} sum;

int grid[SIZE][SIZE];

sum max_sum;

int max_distance;

void saveRegionSum(int i, int j, int value) {
  int a, b;

  for (a = i - max_distance; a <= i + max_distance; a++) {
    if (a < 0 || a >= SIZE) continue;

    for (b = j - max_distance; b <= j + max_distance; b++) {
      if (b < 0 || b >= SIZE) continue;

      if (a == i && b == j) continue;
      
      grid[a][b] += value;

      if (grid[a][b] >= max_sum.value) {
        if (grid[a][b] > max_sum.value || (a < max_sum.x || (a == max_sum.x && b < max_sum.y))) {
          max_sum.value = grid[a][b];
          max_sum.x = a;
          max_sum.y = b;
        }
      }
    }
  }
}

int main () {
  scanf("%d", &max_distance);

  int n_positions;
  scanf("%d", &n_positions);

  for(int i = 0; i < n_positions; i++) {
    int x, y, value;
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &value);

    grid[x][y] = value;
    saveRegionSum(x, y, value);
  }

  printf("%d %d %d", max_sum.x, max_sum.y, max_sum.value);

  return 1;
}