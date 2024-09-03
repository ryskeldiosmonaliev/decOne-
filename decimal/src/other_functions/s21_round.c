#include "../s21_decimal.h"

/** ФУНКЦИЯ достает из value целую часть числа и первое число после точки
 * и заносит их по указателю в переменные:
 * result
 * temp_2
 *
 * **/
int s21_process_rounding(s21_decimal *value, s21_decimal *result,
                         s21_decimal *temp_1, s21_decimal *temp_2) {
  s21_empty_decimal(result);
  /* Округляет Decimal до ближайшего целого числа */
  int exponent = s21_get_exponent(value);
  int sign = s21_get_bit(value, SIGN);
  value->bits[3] = 0;
  s21_decimal scal = {{1, 0, 0, 0}};
  s21_mult_ten(&scal, exponent);
  s21_empty_decimal(temp_2);
  *temp_1 = *value;
  *temp_2 = *value;
  s21_decimal temp_3 = {{0, 0, 0, 0}};
  s21_div_mantiss(temp_1, &scal);
  // получвем целую часть в temp_1
  s21_div_ten(&scal, 1);
  s21_div_mantiss(temp_2, &scal);
  *result = *temp_1;
  // теперь в value хранится дробная часть числа
  temp_3 = *temp_1;
  s21_mult_ten(temp_1, 1);
  s21_mult_ten(&temp_3, exponent);
  s21_sub_mantiss(value, &temp_3);
  s21_sub_mantiss(temp_2, temp_1);
  // s21_print_decimal(value);
  *temp_1 = (s21_decimal){{exponent, 0, 0, 0}};

  return sign;
}

// математическое округление
int s21_round(s21_decimal value, s21_decimal *result) {
  int code = OK;
  s21_decimal temp_2 = {{0, 0, 0, 0}};
  s21_decimal temp_1 = {{0, 0, 0, 0}};
  int sign = s21_process_rounding(&value, result, &temp_1, &temp_2);
  if (temp_2.bits[0] >= 5 && temp_2.bits[0] < 10) {
    s21_PP(result);
  }
  if (sign) {
    s21_set_bit(result, SIGN);
  }
  return code;
}
