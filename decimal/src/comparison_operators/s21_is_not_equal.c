#include "../s21_decimal.h"

int s21_is_not_equal(s21_decimal d1, s21_decimal d2) {
  // в bits[3] в старшем бите находится знак числа, мы будем сравнивать по знаку
  // поэтому вводим две переменные
  int sign_d1 = (d1.bits[3] & 0x80000000) != 0;
  int sign_d2 = (d2.bits[3] & 0x80000000) != 0;
  if (sign_d1 != sign_d2) {
    return TRUE;
  }
  // если знаки не равны, соответственно и числа не равны
  for (int i = 0; i < 3; i++) {
    if (d1.bits[i] != d2.bits[i]) {
      return TRUE;
    }
  }
  // здесь мы сравниваем значения в каждом массиве интов, если они отличаются
  // то числа не равны
  if (s21_get_exponent(&d1) != s21_get_exponent(&d2)) {
    return TRUE;
  }
  // здесь мы сравниваем экспоненты с помощью уже готовой функции get exponent
  return FALSE;  // Числа равны
}
