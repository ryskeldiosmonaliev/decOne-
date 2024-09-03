/*функция принимает 2 децимала и приводит к одинаковой степени*/
#include "../s21_decimal.h"

// Необходимо привести к единой экcпоненте числа
// Для этоко потребуется вычитать / прибавлять
// значения к экспоненте и домножать / округлять мантису

// если при попытке домножить число на 10 чтобы привести
// экспоненту к большей возникает переполнение - то вместо
// умножения используется деление
int s21_normalize(s21_decimal *num1, s21_decimal *num2) {
  int res_ovfw = OK;
  // Get the exponents of the two numbers
  unsigned int exp1 = s21_get_exponent(num1);
  unsigned int exp2 = s21_get_exponent(num2);
  // If exponents are equal, no normalization is needed
  if (exp1 != exp2) {
    int exponent = 0;
    s21_decimal *ptr = NULL;
    int dif_scale = 0;

    // Determine which number has the greater exponent
    if (exp1 > exp2) {
      ptr = num2;
      dif_scale = exp1 - exp2;
      exponent = exp1;
    }

    else {
      ptr = num1;
      dif_scale = exp2 - exp1;
      exponent = exp2;
    }
    // Вот тут мы ориентируемся на переполнение -
    // если оно есть - то вместо усножения будем делить
    s21_decimal tmp = *ptr;
    res_ovfw = s21_mult_ten(&tmp, dif_scale);

    if (!res_ovfw) {
      s21_mult_ten(ptr, dif_scale);
      s21_set_exponent(ptr, exponent);
    } else if (res_ovfw) {
      ptr = exp1 > exp2 ? num1 : num2;
      exponent = exp1 > exp2 ? exp2 : exp1;

      s21_div_ten(ptr, dif_scale);
      s21_set_exponent(ptr, exponent);
    }
  }
  return OK;
}