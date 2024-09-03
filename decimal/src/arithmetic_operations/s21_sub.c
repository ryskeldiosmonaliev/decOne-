#include "../s21_decimal.h"

void s21_sub_mantiss(s21_decimal *d1, s21_decimal *d2) {
  // swap - ecли уменьшаемое меньше вычитаемого - меняем их местами

  if (s21_is_less_mantis(d1, d2)) {
    s21_decimal temp = *d1;
    *d1 = *d2;
    *d2 = temp;
  }

  while (d2->bits[0] != 0 || d2->bits[1] != 0 || d2->bits[2] != 0) {
    // Вычисляем разность без учета переноса
    s21_decimal temp = {{d1->bits[0] ^ d2->bits[0], d1->bits[1] ^ d2->bits[1],
                         d1->bits[2] ^ d2->bits[2], 0}};

    // Вычисляем перенос
    d2->bits[0] = ~d1->bits[0] & d2->bits[0];
    d2->bits[1] = ~d1->bits[1] & d2->bits[1];
    d2->bits[2] = ~d1->bits[2] & d2->bits[2];
    s21_shift_left(d2, 1);

    // Обновляем d1
    *d1 = temp;
  }
}

// (+ - - = ++) (- - + = ++) (+ - +) (- - -)
int s21_sub(s21_decimal reduce, s21_decimal substract,
            s21_decimal *difference) {
  int result = 0;
  if (difference != NULL) {
    s21_decimal neg_val = {{0, 0, 0, 0}};
    s21_negate(substract, &neg_val);
    result = s21_add(neg_val, reduce, difference);
  }
  return result;
}

void s21_sub_mantiss_big(s21_big_dec *d1, s21_big_dec *d2) {
  // swap - ecли уменьшаемое меньше вычитаемого - меняем их местами

  if (s21_is_less_mantis_big(d1, d2)) {
    s21_big_dec temp = *d1;
    *d1 = *d2;
    *d2 = temp;
  }

  while (d2->bits[0] != 0 || d2->bits[1] != 0 || d2->bits[2] != 0 ||
         d2->bits[3] != 0 || d2->bits[4] != 0 || d2->bits[5] != 0) {
    // Вычисляем разность без учета переноса
    s21_big_dec temp = {{d1->bits[0] ^ d2->bits[0], d1->bits[1] ^ d2->bits[1],
                         d1->bits[2] ^ d2->bits[2], d1->bits[3] ^ d2->bits[3],
                         d1->bits[4] ^ d2->bits[4], d1->bits[5] ^ d2->bits[5],
                         0}};

    // Вычисляем перенос
    d2->bits[0] = ~d1->bits[0] & d2->bits[0];
    d2->bits[1] = ~d1->bits[1] & d2->bits[1];
    d2->bits[2] = ~d1->bits[2] & d2->bits[2];
    d2->bits[3] = ~d1->bits[3] & d2->bits[3];
    d2->bits[4] = ~d1->bits[4] & d2->bits[4];
    d2->bits[5] = ~d1->bits[5] & d2->bits[5];

    s21_shift_left_big(d2, 1);

    // Обновляем d1
    *d1 = temp;
  }
}