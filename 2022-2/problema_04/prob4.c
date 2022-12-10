// Nome: Milena de Matos Siqueira, RA: 122044

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_log_2(int n) {
  double log10_2 = log10(2);
  
  return log10(n) / log10_2;
}

int get_quantity(int n, int base_2) {
  int remaining = n - pow(2, base_2);
  int quantity = 1;

  while (remaining > 0) {
    quantity++;
    int current_base_2 = (int) calculate_log_2(remaining);
    remaining = remaining - pow(2, current_base_2);
  }

  return quantity;
}

int get_min_quantity(int n, int base_2) {
  //quantidade sem troco
  int floor_quantity = get_quantity(n, base_2);

  //com troco
  int transfer_value = pow(2, base_2 + 1);  
  int change = transfer_value - n;

  int new_base_2 = (int) calculate_log_2(change);
  int change_quantity = get_quantity(change, new_base_2);
  
  int final_quantity = change_quantity + 1;

  return (floor_quantity < final_quantity) ? floor_quantity : final_quantity;
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
    int int_base_2 = (int) base_2;
    int quantity = get_min_quantity(n, int_base_2);
    printf("%d", quantity);
  }

  return 0;
}