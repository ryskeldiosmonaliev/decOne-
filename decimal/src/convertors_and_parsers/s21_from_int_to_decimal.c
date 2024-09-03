#include "../s21_decimal.h"

/*функция принимает сруктуру децимал и число инт*/
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 0;
  if (dst != NULL) {
    s21_empty_decimal(dst);

    unsigned int mask = 0x80000000;
    if (src == -2147483648) {
      s21_set_bit(dst, SIGN);
      dst->bits[0] = src &= ~mask + 1;
    } else {
      if (src < 0) {
        src *= -1;
        s21_set_bit(dst, SIGN);
      }
      dst->bits[0] = src &= ~mask;
    }
  } else
    res = convertation_error;

  return res;
}
