#include "../s21_decimal.h"

int s21_get_bit_big(s21_big_dec *s21_d, int bit_index) {
  int result = 0;
  int mask = 0;

  // Проверяем, что индекс бита находится в допустимом диапазоне
  if (bit_index < 0 || bit_index > 223) {
    // printf("Ошибка индексации в функции s21_get_bit\n");
    result = index_error;
  } else {
    // Выбираем одно из 4 полей с-труктуры в зависимости от индекса бита
    if (bit_index < 32) {
      mask = powers_of_two[bit_index];
      mask = mask & s21_d->bits[0];
    } else if (bit_index < 64) {
      mask = powers_of_two[bit_index - 32];
      mask = mask & s21_d->bits[1];
    } else if (bit_index < 96) {
      mask = powers_of_two[bit_index - 64];
      mask = mask & s21_d->bits[2];
    } else if (bit_index < 128) {
      mask = powers_of_two[bit_index - 96];
      mask = mask & s21_d->bits[3];
    } else if (bit_index < 160) {
      mask = powers_of_two[bit_index - 128];
      mask = mask & s21_d->bits[4];
    } else if (bit_index < 192) {
      mask = powers_of_two[bit_index - 160];
      mask = mask & s21_d->bits[5];
    } else {
      mask = powers_of_two[bit_index - 192];
      mask = mask & s21_d->bits[6];
    }
    result = mask != 0;
  }

  return result;
}