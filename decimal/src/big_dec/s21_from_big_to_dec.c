#include "../s21_decimal.h"

int s21_from_big_to_dec(s21_big_dec *src, s21_decimal *dst) {
  int code = 0;
  int sign = s21_get_bit_big(src, 223);
  int exp = s21_get_exp_big(src);
  s21_big_dec max_dec = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0, 0, 0}};
  // если мантисса больше максимальной мантиссы
  if (s21_is_less_mantis_big(&max_dec, src)) {
    // если мантисса больше максимальной мантиссы умноженной на 10
    // делим на 10 и уменьшаем экспоненту
    int exp = s21_get_exp_big(src);
    s21_big_dec max = {{0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFFF, 9, 0, 0, 0}};
    while (s21_is_less_mantis_big(&max, src) && exp > 1) {
      s21_div_ten_big(src, 1);
      s21_set_exp_big(src, --exp);
    }
    if (s21_is_less_mantis_big(&max, src))
      // если мантисса осталась больше децимал макс х10 значит +- INF
      code = sign ? 2 : 1;
    else {
      int rem0 = 0;
      // производим банковское округление
      // делим еще раз на 10 для получения дробной части
      rem0 = s21_div_ten_big(src, 1);
      // делим еще раз на 10 для получения целой последней цифры
      unsigned rem1 = s21_div_ten_big(src, 1);
      int whole = rem1;  // последняя целая цифра числа
      int frac = rem0;   // дробная часть числа х10
      if (frac < 5) rem1 = whole;
      if (frac > 5) {
        rem1 = whole + 1;
      }

      if (frac == 5) {
        if (whole % 2 != 0) {
          rem1 = whole + 1;
        } else {
          rem1 = whole;
        }
      }
      // умножаем х10 и складываем части для получения окончательного рез
      s21_mult_10_big(src, 1);
      s21_big_dec tmp = {{0, 0, 0, 0, 0, 0, 0}};
      s21_big_dec suppl = {{rem1, 0, 0, 0, 0, 0, 0}};
      s21_mant_sum_big(src, &suppl, &tmp);
      // устанавливаем экспоненту результата
      s21_set_exp_big(&tmp, --exp);
      // копируем первые 3 и 7 поля в децимал
      for (int i = 0; i < 3; i++) {
        dst->bits[i] = tmp.bits[i];
      }
      dst->bits[3] = tmp.bits[6];
    }
  } else if (exp <= 28) {
    for (int i = 0; i < 3; i++) {
      dst->bits[i] = src->bits[i];
    }
    dst->bits[3] = src->bits[6];
  }
  return code;
}
