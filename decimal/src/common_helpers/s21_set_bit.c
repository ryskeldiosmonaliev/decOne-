#include "../s21_decimal.h"

int s21_set_bit(s21_decimal *s21_d, int bit_index) {
  int result = OK;
  int mask = 0;

  // Проверяем, что индекс бита находится в допустимом диапазоне
  if (bit_index < 0 || bit_index > 127) {
    // printf("Ошибка индексации в функции s21_set_bit\n");
    result = index_error;
  } else {
    // Выбираем одно из 4 полей структуры в зависимости от индекса бита
    if (bit_index < 32) {
      mask = powers_of_two[bit_index];
      s21_d->bits[0] |= mask;
    } else if (bit_index < 64) {
      mask = powers_of_two[bit_index - 32];
      s21_d->bits[1] |= mask;
    } else if (bit_index < 96) {
      mask = powers_of_two[bit_index - 64];
      s21_d->bits[2] |= mask;
    } else {
      mask = powers_of_two[bit_index - 96];
      s21_d->bits[3] |= mask;
    }
  }

  return result;
}

int s21_set_bit_off(s21_decimal *s21_d, int bit_index) {
  int result = OK;
  int mask = 0;

  // Проверяем, что индекс бита находится в допустимом диапазоне
  if (bit_index < 0 || bit_index > 127) {
    // printf("Ошибка индексации в функции s21_set_bit\n");
    result = index_error;
  } else {
    if (bit_index < 32) {
      // маску ставим обратную исходной функции
      mask = ~powers_of_two[bit_index];
      s21_d->bits[0] &= mask;
      // также заменяем битовую операцию
    } else if (bit_index < 64) {
      mask = ~powers_of_two[bit_index - 32];
      s21_d->bits[1] &= mask;
    } else if (bit_index < 96) {
      mask = ~powers_of_two[bit_index - 64];
      s21_d->bits[2] &= mask;
    } else {
      mask = ~powers_of_two[bit_index - 96];
      s21_d->bits[3] &= mask;
    }
  }

  return result;
}