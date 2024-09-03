#include "../s21_decimal.h"

/**
 принимает два децимала. первый больше 1
 первый меньше -1
 равны 0
 **/

int s21_compare(s21_decimal *d1, s21_decimal *d2) {
  int result = FALSE;
  int is_d1_negative = s21_get_bit(d1, SIGN) && !s21_is_zero(d1);
  int is_d2_negative = s21_get_bit(d2, SIGN) && !s21_is_zero(d1);
  // если первое число отрицательное
  if (is_d1_negative && !is_d2_negative) result = -1;
  // если второе число отрицательное
  else if (!is_d1_negative && is_d2_negative)
    result = 1;

  else {
    s21_normalize(d1, d2);
    // нормализуем и пробегаемся по битам
    int flag = 0;
    for (int i = 95; i >= 0 && !flag; i--) {
      int b1 = s21_get_bit(d1, i), b2 = s21_get_bit(d2, i);
      // ecли первый бит выключен 0 а второй включен 1 то мантисса меньше
      // если первый бит 1 а второй 0 то мантисса больше
      int cond1 = !b1 && b2, cond2 = b1 && !b2;
      if (cond1 || cond2) {
        result = cond1 ? -1 : TRUE;
        flag = 1;
      }
      // if (!flag) result = 2;  // инверсия результата при отрицалове
    }
    if (is_d1_negative && is_d2_negative) result = -result;
  }

  return result;
}
