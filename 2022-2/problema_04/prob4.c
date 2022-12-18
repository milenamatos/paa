// Nome: Milena de Matos Siqueira, RA: 122044

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_log_2(int n) {
  return log2(n);
}

int get_min_quantity(int n, int base_2) {
  int remaining = n;
  int current_base_2 = base_2;
  int quantity = 0;

  while (remaining > 0) {
    int current_value = pow(2, current_base_2);
    remaining = abs(remaining - current_value);
    current_base_2 = round(calculate_log_2(remaining));
    quantity++;
  }

  return quantity;
}

int main()
{
  int i, n;

  scanf("%d", &n);

  double base_2 = calculate_log_2(n);

  if (ceil(base_2) == floor(base_2)) {
    printf("1");
  }

  else {
    int int_base_2 = round(base_2);
    int quantity = get_min_quantity(n, int_base_2);
    printf("%d", quantity);
  }

  return 0;
}