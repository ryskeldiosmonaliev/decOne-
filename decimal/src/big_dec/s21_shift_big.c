#include "../s21_decimal.h"

int s21_shift_left_big(s21_big_dec *decimal, int shift_count) {
  int overflow = FALSE;  // результат, если true - произошло переполнение
  unsigned int carry = 0;  // перенос бита
  for (int shift = 0; shift < shift_count && !overflow; shift++) {
    carry = 0;
    if (powers_of_two[31] & decimal->bits[5]) {
      overflow = TRUE;
    }
    for (int i = 0; i < 6 && !overflow; i++) {
      unsigned int current = decimal->bits[i];
      decimal->bits[i] =
          (current << 1) |
          carry;  // сдвигаем текущий элемент влево и добавляем перенос
      carry = (current >> 31) & 1;  // получаем старший бит для переноса
    }
    // Проверяем, не произошло ли переполнение после сдвига на 1 позицию
    if (carry) {
      overflow = TRUE;  // == number_is_too_large
    }
  }
  return overflow;
}

int s21_shift_right_big(s21_big_dec *decimal, int shift_count) {
  int result = OK;
  if (shift_count > 0 && shift_count <= 192) {
    for (int i = 0; i < shift_count; i++) {
      int carry4 = (decimal->bits[5] & 1) << 31;
      int carry3 = (decimal->bits[4] & 1) << 31;
      int carry2 = (decimal->bits[3] & 1) << 31;
      int carry1 = (decimal->bits[2] & 1) << 31;  // последний бит второго поля
      int carry0 = (decimal->bits[1] & 1) << 31;  // последний бит первого поля
      decimal->bits[5] = (decimal->bits[5] >> 1);
      decimal->bits[0] = (decimal->bits[0] >> 1) | carry0;
      decimal->bits[1] = (decimal->bits[1] >> 1) | carry1;
      decimal->bits[2] = (decimal->bits[2] >> 1) | carry2;
      decimal->bits[3] = (decimal->bits[3] >> 1) | carry3;
      decimal->bits[4] = (decimal->bits[4] >> 1) | carry4;
    }
  } else {
    result = index_error;  // Ошибка, если shift_count вне допустимого диапазона
  }
  return result;
}
