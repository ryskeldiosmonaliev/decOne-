#include "../s21_decimal.h"

unsigned int s21_get_exponent(s21_decimal *s21_d) {
  unsigned int result = 0;
  result = s21_d->bits[3];
  if (s21_get_bit(s21_d, SIGN)) {
    result -= powers_of_two[31];
  }
  return result >> 16;
}

int s21_set_exponent(s21_decimal *s21_d, unsigned char val) {
  int result = OK;

  if (val <= 28) {
    // очищаем существующую экспоненту сдвигом вправа
    s21_d->bits[3] &= ~(0xFF << 16);  // Clear bits 16-23
    s21_d->bits[3] |= (val << 16);  // Помещаем 8 бит беззнакового чара на 16-23
                                    // биты инта по 3му индексу
  }

  else {
    result = index_error;
  }
  return result;
}

unsigned int s21_get_exp_big(s21_big_dec *s21_d) {
  unsigned int result = 0;
  result = s21_d->bits[6];
  if (s21_get_bit_big(s21_d, 223)) {
    result -= powers_of_two[31];
  }
  return result >> 16;
}

int s21_set_exp_big(s21_big_dec *s21_d, unsigned char val) {
  int result = OK;
  // очищаем существующую экспоненту сдвигом вправа
  s21_d->bits[6] &= ~(0xFF << 16);  // Clear bits 16-23
  s21_d->bits[6] |= (val << 16);

  return result;
}
