#include "../s21_decimal.h"

void s21_empty_decimal(s21_decimal *s21_d) {
  if (s21_d != NULL) {
    *s21_d = (s21_decimal){{0, 0, 0, 0}};
  }
}

int s21_is_spec_flot_val(float input_num) {
  return (input_num == 0.0) || (isinf(input_num) == TRUE) ||
         (isnan(input_num) == TRUE) ||
         (fabsf(input_num) > MAX_FLOAT_FITTING_INTO_DECIMAL) ||
         (fabsf(input_num) < MIN_FLOAT_FITTING_INTO_DECIMAL);
}

/** *
 * - Если числа слишком малы (0 < |x| < 1e-28), возвращай ошибку и значение,
 * равное 0*.
 * - Если числа слишком велики (|x| > 79,228,162,514,264,337,593,543,950,335)
 * или равны бесконечности, возвращай ошибку*.**/
int s21_special_values(float src, s21_decimal *dst) {
  int code = OK;
  if (src == 0.0) {
    code = OK;
    *dst = (s21_decimal){{0, 0, 0, 0}};
    if (signbit(src) != 0) {
      s21_set_bit(dst, SIGN);
    }
  } else {
    code = convertation_error;
    if (fabsf(src) < MIN_FLOAT_FITTING_INTO_DECIMAL) {
      *dst = (s21_decimal){{0, 0, 0, 0}};
    } else {
      if (isinf(src) == TRUE) {
        *dst = DECIMAL_POSITIVE_INFINITY;
      } else if (isnan(src) == TRUE) {
        *dst = DECIMAL_POSITIVE_NAN;
      } else /* fabsf(src) > MAX_FLOAT */ {
        *dst = DECIMAL_POSITIVE_INFINITY;
      }
      if (signbit(src) != 0) {
        s21_set_bit(dst, SIGN);
      }
    }
  }
  return code;
}

int s21_get_float_exp_from_string(char *str) {
  int result = 0;
  char *ptr = str;
  while (*ptr) {
    if (*ptr == 'E') {
      ptr++;
      result = strtol(ptr, NULL, 10);
      break;
    }
    ptr++;
  }
  return result;
}

/**
 * Проверяет, присутствует ли символ в строке.
 */
int s21_in(char c, char *str) {
  int result = 0;
  if (str != NULL) {
    for (int i = 0; str[i] != '\0'; i++) {
      if (str[i] == c) {
        result = 1;
      }
    }
  }
  return result;
}

s21_decimal s21_string_to_decimal(char *sci_str, int exponent) {
  int fl_E = 0, negative_exponent = 0, ten_pow = 0, percision_limit_end = 0;
  s21_decimal s21_d = D0;
  // парсим строку начиная с последнего символа
  // и заносим значение в децимал
  for (int i = strlen(sci_str) - 1; i >= 0; i--) {
    if (fl_E && s21_in(sci_str[i], "123456789")) {
      s21_d.bits[0] += (sci_str[i] - '0') * pow(10, ten_pow++);
    } else if (ten_pow && sci_str[i] == '0') {
      s21_d.bits[0] += (sci_str[i] - '0') * pow(10, ten_pow++);
    } else if (s21_in(sci_str[i], "Ee")) {
      fl_E = 1;
    } else if (s21_in(sci_str[i], "-")) {
      negative_exponent = 1;
    }
  }
  // тест driven development
  // объяснить как оно работает трудно
  if (exponent < -22) {
    exponent = -22;
    percision_limit_end = 1;
  }
  if (negative_exponent) {
    exponent = abs(exponent) + 6;
    s21_set_exponent(&s21_d, exponent);
    if (percision_limit_end == FALSE) {
      s21_mult_ten(&s21_d, abs(7 - ten_pow));
    }
  } else {
    if ((exponent - ten_pow + 1) > 0) {
      s21_mult_ten(&s21_d, (exponent - ten_pow + 1));
    } else {
      s21_set_exponent(&s21_d, abs(exponent - ten_pow + 1));
    }
  }
  return s21_d;
}

/**
 * Преобразует число с плавающей запятой в представление s21_decimal.
 **/
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int code = OK;
  // 1. отработать случай когда децимал не инициализирован
  if (dst == NULL) {
    return convertation_error;
  }
  // 2. проверить float на специальные значения децимала
  else if (s21_is_spec_flot_val(src)) {
    // 3. установить специальные значения если есть соответствия
    code = s21_special_values(src, dst);
  } else {
    // 4. инициализировать децимал нулями и результат
    *dst = D0;
    s21_decimal result = D0;
    // 5. создать строку с нулями на 64 символа
    char E_str[64] = {'\0'};
    // 6. записать строковое представление с стандартной точностью
    // седбмая значющая цифра округляетмя по математичемкому принципу
    sprintf(E_str, "%.6E", fabsf(src));
    // 7. получаем экспоненту из строки
    int exponent = s21_get_float_exp_from_string(E_str);
    // 8. расчитываем точность, если число меньше
    // минимальной экспоненты - перибавляем к ней максимальную
    // допустимую точность
    int float_precision = exponent <= -22 ? exponent + 28 : 6;
    // получаем строку с финальной точностью для извлечения
    // значения и переноса в децимал
    snprintf(E_str, 63, "%.*E", float_precision, fabsf(src));
    // вызываем функцию которая преобразует строку
    // в нотации к децимал
    result = s21_string_to_decimal(E_str, exponent);
    // ставим знак - если он есть
    if (signbit(src) != 0) {
      s21_set_bit(&result, SIGN);
    }
    // перекидываем результат
    *dst = result;
  }
  return code;
}
