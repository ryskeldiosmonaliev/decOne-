#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  // достаю знак
  int code = OK, sign = s21_get_bit(&src, SIGN);
  // проверяю на факап
  if (dst == NULL) {
    code = convertation_error;
  }
  // создаю переменную для хранения целой части числа
  s21_decimal tmp = {{0, 0, 0, 0}};
  // выключаю знак чтобы не мешал оперировать
  s21_set_bit_off(&src, SIGN);
  // отбрасываю дробную часть
  s21_truncate(src, &tmp);
  // результат округления помещаю в src
  src = tmp;
  // теперь tmp - это максимальный инт для сравнения
  tmp = (s21_decimal){{INT_MAX, 0, 0, 0}};
  // если децимал больше максимального занчения инта
  if (code == OK && s21_is_greater(src, tmp)) {
    code = convertation_error;  // Ошибки лучшие учителя
  }
  // преобразование
  else if (code == OK) {
    // первое поле это мантиса
    *dst = src.bits[0];
    // ставим знак
    if (sign) {
      *dst = ~*dst + 1;
    }
  }
  // возвращаем код
  return code;
}
