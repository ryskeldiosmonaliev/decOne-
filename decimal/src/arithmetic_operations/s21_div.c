#include "../s21_decimal.h"

int s21_div_ten(s21_decimal *decimal, int times) {
  int result = OK;
  while (times--) {
    s21_decimal ten = {{10, 0, 0, 0}};
    unsigned int rem = s21_div_mantiss(decimal, &ten);
    result = (int)rem;
  }
  return result;
}
int s21_div_ten_big(s21_big_dec *decimal, int times) {
  int result = OK;

  while (times--) {
    s21_big_dec ten = {{10, 0, 0, 0, 0, 0, 0}};
    unsigned int rem = s21_div_mantiss_big(decimal, &ten);
    result = (int)rem;
  }

  return result;
}

/* функция делит мантисы - только
положительные и сохраняет результат в d1
 по указателю , возвращает остаток от деления
Деление методом вычитания */
unsigned int s21_div_mantiss(s21_decimal *a, s21_decimal *b) {
  unsigned int rem = 0;  // для сохранения остатка от деления
  s21_decimal result = {{0, 0, 0, 0}};
  // начинаем с 2х в самой большой степени
  for (int i = 95; i >= 0; i--) {
    // копия делителя
    s21_decimal tmp_1 = *b;
    int overflow = s21_shift_left(&tmp_1, i);
    // создвем временную переменную усножая делитель
    // на два в степени i - переменная tmp_1
    // если нет ПЕРЕПОЛНЕНИЯ
    if ((s21_is_less_mantis(&tmp_1, a) || s21_is_equal(tmp_1, *a)) &&
        !overflow) {
      s21_sub_mantiss(a, &tmp_1);

      // создаю маску слогаемого
      s21_decimal tmp_2 = {{0, 0, 0, 0}};
      s21_set_bit(&tmp_2, i);
      // сохраняю прошлый результат вычислений
      s21_decimal tmp_3 = result;
      // добавляю к нему маcку слогаемого
      s21_mant_sum(&tmp_2, &tmp_3, &result);
    }
  }
  rem = a->bits[0];
  // Cохранится остаток деления - из него мы вычли
  // целую часть делителя
  *a = result;  //
  return rem;
}

int s21_mult_10_big(s21_big_dec *num, int times) {
  s21_big_dec copy = *num;
  int result = 0;
  while (times && !result) {
    // mul_ten(s21_dec num)
    /*умножаем число на 2 сдвигом мантиссы влево на 1*/
    s21_shift_left_big(num, 1);
    /*умножаем копию на 4 сдвигом мантиссы влево на 3*/
    s21_shift_left_big(&copy, 3);
    // s21_print_decimal(&copy);
    times--;
    s21_big_dec fin = {{0, 0, 0, 0, 0, 0}};
    /*складываем полученные числа побитово, в результате имеем умножение на
     * 10*/
    s21_mant_sum_big(num, &copy, &fin);

    *num = copy = fin;
  }
  return result;
};

int s21_div(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  *result = D0;
  int code = OK;
  // деление на ноль
  if (s21_is_zero(&value2)) {
    code = division_by_0;  // 3
  } else {
    // знак
    int sign = s21_get_bit(&value1, SIGN) ^ s21_get_bit(&value2, SIGN);
    // эуспоненты
    int v1_exp = s21_get_exponent(&value1);
    int v2_exp = s21_get_exponent(&value2);
    // разница между экспонентами и сравнение (1) первая меньше второй
    int exp_cond[] = {abs(v1_exp - v2_exp), (v1_exp < v2_exp)};
    // инициализация бигдецималов для нормализации мантис
    s21_big_dec bd1 = {
        {0, 0, 0, value1.bits[0], value1.bits[1], value1.bits[2]}};
    s21_big_dec bd2 = {
        {0, 0, 0, value2.bits[0], value2.bits[1], value2.bits[2]}};
    // домножаем на 10 децимал с меньшей экспонентой
    exp_cond[1] ? s21_mult_10_big(&bd1, exp_cond[0])
                : s21_mult_10_big(&bd2, exp_cond[0]);

    // тут мог быть алгоритм деления, но я не смог его написать

    // Наверное
    if (sign) {
      s21_set_bit(result, SIGN);
    }
  }
  return code;
}

unsigned int s21_div_mantiss_big(s21_big_dec *a, s21_big_dec *b) {
  unsigned int rem = 0;  // для сохранения остатка от деления
  s21_big_dec result = {{0, 0, 0, 0, 0, 0, 0}};
  // начинаем с 2х в самой большой степени
  for (int i = 191; i >= 0; i--) {
    // копия делителя
    s21_big_dec tmp_1 = *b;
    int overflow = s21_shift_left_big(&tmp_1, i);
    // создвем временную переменную усножая делитель
    // на два в степени i - переменная tmp_1
    // если нет ПЕРЕПОЛНЕНИЯ
    if ((s21_is_less_mantis_big(&tmp_1, a) ||
         s21_is_mant_equal_big(&tmp_1, a)) &&
        !overflow) {
      s21_sub_mantiss_big(a, &tmp_1);

      // создаю маску слогаемого
      s21_big_dec tmp_2 = {{0, 0, 0, 0, 0, 0, 0}};
      s21_set_bit_big(&tmp_2, i);
      // сохраняю прошлый результат вычислений
      s21_big_dec tmp_3 = result;
      // добавляю к нему маcку слогаемого
      s21_mant_sum_big(&tmp_2, &tmp_3, &result);
    }
  }
  rem = a->bits[0];
  // Cохранится остаток деления - из него мы вычли
  // целую часть делителя
  *a = result;
  return rem;
}
