#include "../s21_decimal.h"

int s21_mant_sum_big(s21_big_dec *value_1, s21_big_dec *value_2,
                     s21_big_dec *result) {
  int code = OK;
  unsigned int carry = 0;  // Перенос
  unsigned int temp;  // Временная переменная для хранения суммы одном из полей
  int exp = s21_get_exp_big(value_1);

  // Сложение первых 6 полей (мантиса)
  for (int i = 0; i < 6; i++) {
    temp = value_1->bits[i] + value_2->bits[i] +
           carry;  // Сложение с учетом переноса
    carry = (temp < value_1->bits[i] || (carry && temp == value_1->bits[i]))
                ? 1
                : 0;
    result->bits[i] = temp;
    // Проверяем, произошел ли перенос
    // Записываем результат
  }
  // Проверка переполнения ??????????наверное не нужна
  if (carry) {
    code = TRUE;  // Устанавливаем код ошибки переполнения
  }
  s21_set_exp_big(result, exp);
  return code;  // выполнение
}