#include "../s21_decimal.h"

/**
 * Функция инвертирует знак числа, хранящегося в формате s21_decimal.
 * Если число положительное, оно становится отрицательным, и наоборот.
 * Возвращает OK при успешной операции.
 */
int s21_negate(s21_decimal value, s21_decimal *result) {
  int code = 0;
  if (result == NULL) {
    code = calculation_error;
  } else {
    // Инвертируем знаковый бит
    *result = value;
    result->bits[3] ^= 0x80000000;
  }
  return code;
}
