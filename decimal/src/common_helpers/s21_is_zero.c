#include "../s21_decimal.h"

/**
 * проверка значения децимала на ноль
 * если 0 возвращает 1
 * иначе 0.
 * zn
 **/
int s21_is_zero(s21_decimal *value) {
  return value->bits[0] == 0 && value->bits[1] == 0 && value->bits[2] == 0;
}