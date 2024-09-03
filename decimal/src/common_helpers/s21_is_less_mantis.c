#include "../s21_decimal.h"

int s21_is_less_mantis(s21_decimal *d1, s21_decimal *d2) {
  int result = FALSE;

  int flag = 0;
  for (int i = 95; i >= 0 && !flag; i--) {
    int b1 = s21_get_bit(d1, i), b2 = s21_get_bit(d2, i);
    // ecли первый бит выключен 0 а второй включен 1 то мантисса меньше
    // если первый бит 1 а второй 0 то мантисса больше
    int cond1 = !b1 && b2, cond2 = b1 && !b2;
    if (cond1 || cond2) {
      result = cond1 ? TRUE : FALSE;
      flag = 1;
    }  // значит результат по умолчанию false
  }

  return result;
}
int s21_is_less_mantis_big(s21_big_dec *d1, s21_big_dec *d2) {
  int result = FALSE;

  int flag = 0;
  for (int i = 191; i >= 0 && !flag; i--) {
    int b1 = s21_get_bit_big(d1, i), b2 = s21_get_bit_big(d2, i);
    // ecли первый бит выключен 0 а второй включен 1 то мантисса меньше
    // если первый бит 1 а второй 0 то мантисса больше
    int cond1 = !b1 && b2, cond2 = b1 && !b2;
    if (cond1 || cond2) {
      result = cond1 ? TRUE : FALSE;
      flag = 1;
    }  // значит результат по умолчанию false
  }

  return result;
}
int s21_is_mant_equal_big(s21_big_dec *a, s21_big_dec *b) {
  int result = TRUE;

  for (int i = 0; i < 7; i++) {
    if (a->bits[i] != b->bits[i]) result = FALSE;
  }
  return result;
}