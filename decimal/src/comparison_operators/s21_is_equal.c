#include "../s21_decimal.h"

int s21_is_equal(s21_decimal d1, s21_decimal d2) {
  int result = TRUE;
  int allzerous = TRUE;
  if (d1.bits[0] != d2.bits[0]) result = FALSE;
  if (d1.bits[0] || d2.bits[0]) allzerous = FALSE;
  if (d1.bits[1] != d2.bits[1]) result = FALSE;
  if (d1.bits[1] || d2.bits[1]) allzerous = FALSE;
  if (d1.bits[2] != d2.bits[2]) result = FALSE;
  if (d1.bits[2] || d2.bits[2]) allzerous = FALSE;
  if (s21_get_exponent(&d2) != s21_get_exponent(&d1)) result = FALSE;
  if (s21_get_exponent(&d2) || s21_get_exponent(&d1)) allzerous = FALSE;
  if ((allzerous == FALSE && result == TRUE) &&
      (s21_get_bit(&d1, SIGN) != s21_get_bit(&d2, SIGN)))
    result = FALSE;
  return result;
}
