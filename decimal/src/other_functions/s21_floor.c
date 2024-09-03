#include "../s21_decimal.h"

// округление в сеньшую сторону
int s21_floor(s21_decimal value, s21_decimal *result) {
  int code = OK;
  s21_decimal temp_2 = {{0, 0, 0, 0}};
  s21_decimal temp_1 = {{0, 0, 0, 0}};
  int sign = s21_process_rounding(&value, result, &temp_1, &temp_2);
  if (sign) {
    s21_PP(result);
    s21_set_bit(result, SIGN);
  }
  return code;
}
