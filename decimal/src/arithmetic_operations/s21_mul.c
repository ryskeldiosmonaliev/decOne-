#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = OK;
  if (result != NULL) {
    if (s21_is_zero(&value_1)) {
      s21_empty_decimal(result);
    } else if (s21_is_zero(&value_2))
      s21_empty_decimal(result);
    else {
      int result_sign = 0;
      int sign1 = s21_get_bit(&value_1, SIGN),
          sign2 = s21_get_bit(&value_2, SIGN);
      s21_empty_decimal(result);
      // (+-) || (-+)
      if ((sign1 || sign2) && !(sign1 && sign2)) {
        result_sign = 1;
      }
      int exp1 = s21_get_exponent(&value_1), exp2 = s21_get_exponent(&value_2);
      int exp = exp1 + exp2;
      s21_big_dec big_val1 = {{0, 0, 0, 0, 0, 0, 0}},
                  big_val2 = {{0, 0, 0, 0, 0, 0, 0}};
      // конвертируем в биг децимал
      s21_from_dec_to_big(&value_1, &big_val1);
      s21_from_dec_to_big(&value_2, &big_val2);
      // перемножаем мантиссы
      s21_mul_mant_big(&big_val1, &big_val2);
      s21_set_exp_big(&big_val1, exp);
      // устанавливаем результирующую степень и
      // преобразуем обратно в децимал
      code = s21_from_big_to_dec(&big_val1, result);
      if (result_sign && !code) {
        s21_set_bit(result, SIGN);
      } else if (result_sign && code)
        code = number_is_too_small;
      else
        s21_set_bit_off(result, SIGN);
    }
  }
  return code;
}

int s21_mult_ten(s21_decimal *num, int mult_val) {
  s21_decimal copy = *num;

  int result = 0;
  if (s21_is_possible_x10(num)) {
    while (mult_val && !result) {
      // mul_ten(s21_dec num)
      /*умножаем число на 2 сдвигом мантиссы влево на 1*/
      result = s21_shift_left(num, 1);
      /*умножаем копию на 4 сдвигом мантиссы влево на 3*/
      result = s21_shift_left(&copy, 3);
      // s21_print_decimal(&copy);
      mult_val--;
      s21_decimal fin = {{0, 0, 0, 0}};
      /*складываем полученные числа побитово, в результате имеем умножение на
       * 10*/
      result = s21_mant_sum(num, &copy, &fin);
      *num = copy = fin;
    }
  } else
    result = 1;
  return result;
}

int s21_is_mant_equal(s21_decimal *a, s21_decimal *b) {
  int result = TRUE;

  for (int i = 0; i < 3; i++) {
    if (a->bits[i] != b->bits[i]) result = FALSE;
  }
  return result;
}

// из-за с оверфлоу тут хер пойми как его отследить
// вроде я сделал
int s21_mul_mant_big(s21_big_dec *a, s21_big_dec *b) {
  int code = OK;
  s21_big_dec result = {{0, 0, 0, 0, 0, 0, 0}};
  int flag = OK;
  while (s21_is_zero_big(b) == FALSE && flag == OK) {
    s21_big_dec tmp = {{0, 0, 0, 0, 0, 0, 0}};

    if (s21_get_bit_big(b, 0)) {
      tmp = result;
      code = s21_mant_sum_big(&tmp, a, &result);
    }
    s21_shift_right_big(b, 1);
    flag = s21_shift_left_big(a, 1);
  }
  *a = result;
  return code;
}

int s21_mul_mant(s21_decimal *a, s21_decimal *b) {
  int code = OK;
  s21_decimal result = {{0, 0, 0, 0}};
  if (s21_is_zero(a)) {
    result = *a;
  } else if (s21_is_zero(b)) {
    result = *b;
  } else if (a->bits[0] == 1 && a->bits[1] == 0 && a->bits[2] == 0) {
    result = *b;
  } else if (b->bits[0] == 1 && b->bits[1] == 0 && b->bits[2] == 0) {
    result = *a;
  } else {
    int flag = OK;
    int ovfw = 0;

    while (s21_is_zero(b) == FALSE && flag == OK) {
      s21_decimal tmp = {{0, 0, 0, 0}};

      if (s21_get_bit(b, 0)) {
        tmp = result;
        code = s21_mant_sum(&tmp, a, &result);
        ovfw += s21_get_bit(&result, 95);
      }
      s21_shift_right(b, 1);
      flag = s21_shift_left(a, 1);
    }
    if (s21_is_zero(&result) && flag) ovfw++;
    // попробуем проверять результат на переполнение
    if (ovfw) {
      code = number_is_too_large;
      *a = (s21_decimal){{0, 0, 0, 0}};
    }
  }
  *a = result;
  return code;
}
