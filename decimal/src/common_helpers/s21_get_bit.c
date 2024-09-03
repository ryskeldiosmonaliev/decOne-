#include "../s21_decimal.h"

// 0 - 31 степень двойки
unsigned int powers_of_two[] = {
    1,    // 0
    2,    // 1
    4,    // 2
    8,    // 3
    16,   // 4
    32,   // 5
    64,   // 6
    128,  // 7

    256,    // 8
    512,    // 9
    1024,   // 10
    2048,   // 11
    4096,   // 12
    8192,   // 13
    16384,  // 14
    32768,  // 15

    65536,    // 16
    131072,   // 17
    262144,   // 18
    524288,   // 19
    1048576,  // 20
    2097152,  // 21
    4194304,  // 22
    8388608,  // 23

    16777216,    // 24
    33554432,    // 25
    67108864,    // 26
    134217728,   // 27
    268435456,   // 28
    536870912,   // 29
    1073741824,  // 30
    2147483648   // 31
};

int s21_get_bit(s21_decimal *s21_d, int bit_index) {
  int result = 0;
  int mask = 0;

  // Проверяем, что индекс бита находится в допустимом диапазоне
  if (bit_index < 0 || bit_index > 127) {
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
    } else {
      mask = powers_of_two[bit_index - 96];
      mask = mask & s21_d->bits[3];
    }
    result = mask != 0;
  }

  return result;
}