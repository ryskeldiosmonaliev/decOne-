#include "../s21_decimal.h"
// проверка возможно ли умножение на 10 мантиссы без переполнения
int s21_is_possible_x10(s21_decimal *value) {
  int flag = 0;
  int result = 0;
  // максимальное число которе можно умножать
  s21_decimal max = {{0x99999999, 0x99999999, 0x19999999, 0x00000000}};
  for (int i = 95; i >= 0 && !flag; i--) {
    int b1 = s21_get_bit(value, i), b2 = s21_get_bit(&max, i);
    int cond1 = !b1 && b2, cond2 = b1 && !b2;
    if (cond1 || cond2) {
      result = cond1 ? TRUE : FALSE;
      flag = 1;
    }
  }
  return result;
}
