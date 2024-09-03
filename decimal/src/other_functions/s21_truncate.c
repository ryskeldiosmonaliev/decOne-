#include "../s21_decimal.h"

/** Отбрасывает дробную часть **/
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int code = OK;
  s21_decimal temp_2 = {{0, 0, 0, 0}};
  s21_decimal temp_1 = {{0, 0, 0, 0}};
  int sign = s21_process_rounding(&value, result, &temp_1, &temp_2);
  if (sign) {
    s21_set_bit(result, SIGN);
  }
  return code;
}
