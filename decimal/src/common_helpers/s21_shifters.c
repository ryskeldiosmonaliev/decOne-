#include "../s21_decimal.h"

int s21_shift_left(s21_decimal *decimal, int shift_count) {
  int overflow = FALSE;  // результат, если true - произошло переполнение
  unsigned int carry = 0;  // перенос бита
  for (int shift = 0; shift < shift_count && !overflow; shift++) {
    carry = 0;
    if (powers_of_two[31] & decimal->bits[2]) {
      overflow = TRUE;
    }
    for (int i = 0; i < 3 && !overflow; i++) {
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

int s21_shift_right(s21_decimal *decimal, int shift_count) {
  int result = OK;
  if (shift_count > 0 && shift_count <= 96) {
    for (int i = 0; i < shift_count; i++) {
      int carry1 = (decimal->bits[2] & 1) << 31;  // последний бит второго поля
      int carry0 = (decimal->bits[1] & 1) << 31;  // последний бит первого поля
      decimal->bits[2] = (decimal->bits[2] >> 1);
      decimal->bits[0] = (decimal->bits[0] >> 1) | carry0;
      decimal->bits[1] = (decimal->bits[1] >> 1) | carry1;
    }
  } else {
    result = index_error;  // Ошибка, если shift_count вне допустимого диапазона
  }
  return result;
}
