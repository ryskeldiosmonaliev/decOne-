#include "../s21_decimal.h"

// increment  ++  (+= 1)
void s21_PP(s21_decimal *decimal) {
  s21_decimal temp_1 = {
      {decimal->bits[0], decimal->bits[1], decimal->bits[2], 0}};
  s21_decimal temp_2 = {{1, 0, 0, 0}};
  s21_mant_sum(&temp_1, &temp_2, decimal);
}

// почти как round но если у нас 5 то мы округляем его до ближайшено четного
int s21_banking_round(s21_decimal *value, s21_decimal *result) {
  int code = OK;
  s21_decimal temp_2 = {{0, 0, 0, 0}};
  s21_decimal temp_1 = {{0, 0, 0, 0}};
  int sign = s21_process_rounding(value, result, &temp_1, &temp_2);

  if (temp_2.bits[0] > 5 && temp_2.bits[0] < 10) {
    s21_PP(result);
  } else if (temp_2.bits[0] == 5) {
    s21_mult_ten(&temp_2, (int)temp_1.bits[0] - 1);
    if (s21_is_equal(temp_2, *value)) {
      if (s21_get_bit(result, 0) == 1) {
        s21_PP(result);
      }
    } else {
      s21_PP(result);
    }
  }
  if (sign) s21_set_bit(result, SIGN);
  return code;
}
