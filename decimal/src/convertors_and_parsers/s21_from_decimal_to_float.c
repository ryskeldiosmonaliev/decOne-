#include "../s21_decimal.h"

// Функция принимает decimal и возвращает float
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = 0;                         // нолик
  int sign = s21_get_bit(&src, SIGN);     // знак
  if (!dst) result = convertation_error;  // ошибочка
  // нолик отрабатываем
  else if ((src.bits[0] == 0 && src.bits[1] == 0 && src.bits[2] == 0)) {
    *dst = 0.0;
    if (sign) *dst = -0.0;
  }
  // общий случай
  else {
    *dst = 0.0;
    // проходимся по степеням двойки и прибавляем к src
    for (int i = 95; i >= 0; i--) {
      if (s21_get_bit(&src, i)) {
        *dst += (float)pow(2, i);
      }
    }
    // cтавим экспоненту и знак
    int exp = s21_get_exponent(&src);
    if (exp != 0) *dst /= (float)pow(10, exp);
    if (sign) *dst *= -1;
  }
  return result;
}
