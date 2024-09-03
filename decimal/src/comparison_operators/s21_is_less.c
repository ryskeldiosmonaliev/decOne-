#include "../s21_decimal.h"

int s21_is_less(s21_decimal d1, s21_decimal d2) {
  int result = FALSE;
  int res = s21_compare(&d1, &d2);
  if (res == -1) result = 1;
  return result;
}
