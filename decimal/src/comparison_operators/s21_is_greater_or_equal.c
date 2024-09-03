#include "../s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal d1, s21_decimal d2) {
  int result = FALSE;
  if (s21_compare(&d1, &d2) >= 0) result = TRUE;
  return result;
}
