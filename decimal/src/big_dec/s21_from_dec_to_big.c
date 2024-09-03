#include "../s21_decimal.h"

int s21_from_dec_to_big(s21_decimal *src, s21_big_dec *dst) {
  for (int i = 0; i < 3; i++) {
    dst->bits[i] = src->bits[i];
  }
  for (int i = 3; i < 5; i++) dst->bits[i] = 0;
  dst->bits[6] = src->bits[3];
  return 0;
}
