#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = OK;
  if (result != NULL) {
    int result_sign = 0;
    int sign1 = s21_get_bit(&value_1, SIGN),
        sign2 = s21_get_bit(&value_2, SIGN);
    s21_set_bit_off(&value_1, SIGN);
    s21_set_bit_off(&value_2, SIGN);
    s21_normalize(&value_1, &value_2);
    // (-+)
    if (sign1 && !sign2) {
      if (s21_is_less_mantis(&value_2, &value_1)) result_sign = 1;
      *result = value_2;
      s21_sub_mantiss(result, &value_1);
    }
    // (+-)
    else if (sign2 && !sign1) {
      *result = value_1;
      if (s21_is_less_mantis(&value_1, &value_2)) result_sign = 1;
      s21_sub_mantiss(result, &value_2);
    }
    // (--) && (++)
    else {
      code = s21_mant_sum(&value_1, &value_2, result);
      if (sign1) s21_set_bit(result, SIGN);
    }
    if (result_sign) {
      s21_set_bit(result, SIGN);
    }

    int exponent = s21_get_exponent(&value_1);
    s21_set_exponent(result, exponent);
  }
  return code;
}

int s21_mant_sum(s21_decimal *value_1, s21_decimal *value_2,
                 s21_decimal *result) {
  int code = OK;
  unsigned int carry = 0;  // Перенос
  unsigned int temp =
      0;  // Временная переменная для хранения суммы одном из полей
  int exp = s21_get_exponent(value_1);

  // Сложение первых трех полей (мантиса)
  for (int i = 0; i < 3; i++) {
    temp = value_1->bits[i] + value_2->bits[i] +
           carry;  // Сложение с учетом переноса
    carry = (temp < value_1->bits[i] || (carry && temp == value_1->bits[i]))
                ? 1
                : 0;
    result->bits[i] = temp;
    // Проверяем, произошел ли перенос
    // Записываем результат
  }
  // Проверка переполнения
  if (carry) {
    code = TRUE;  // Устанавливаем код ошибки переполнения
    // Обнуляем результат при переполнении
    for (int i = 0; i < 3; i++) {
      result->bits[i] = 0;
    }
  }
  s21_set_exponent(result, exp);
  return code;  // выполнение
}
