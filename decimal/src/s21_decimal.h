#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// индекс знакового бита
#define SIGN 127
// Максимальное значение мантиссы
#define MAX_MANTISSA 79228162514264337593543950335.0
// Минимальное значение мантиссы
#define MIN_MANTISSA -79228162514264337593543950335.0
// Положительная бесконечность инта 32 (+∞): 0x7F800000
// 0B01111111100000000000000000000000
#define FLT_INF_POS 0B01111111100000000000000000000000
// Отрицательная бесконечность (-∞): 0xFF800000
// 0B11111111100000000000000000000000
#define FLT_INF_NEG 0B11111111100000000000000000000000

#define D0 ((s21_decimal){{0, 0, 0, 0}})

#define MAX_FLOAT_FITTING_INTO_DECIMAL 79228157791897854723898736640.0f
#define MIN_FLOAT_FITTING_INTO_DECIMAL \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f

#define DECIMAL_POSITIVE_INFINITY \
  ((s21_decimal){{0x0, 0x0, 0x0, 0b01111000000000000000000000000000}})
#define DECIMAL_NEGATIVE_INFINITY \
  ((s21_decimal){{0x0, 0x0, 0x0, 0b11111000000000000000000000000000}})
#define DECIMAL_POSITIVE_NAN \
  ((s21_decimal){{0x0, 0x0, 0x0, 0b01111100000000000000000000000000}})
#define DECIMAL_NEGATIVE_NAN \
  ((s21_decimal){{0x0, 0x0, 0x0, 0b11111100000000000000000000000000}})

// возвращаемые значения
enum errors {
  // Арифметические ошибки // Arithmetic Operators
  OK = 0,
  number_is_too_large = 1,
  number_is_too_small = 2,
  division_by_0 = 3,
  // Ошибки сравнения // Comparison Operators
  TRUE = 1,
  FALSE = 0,
  // Ошибка конвертации // convertors and parsers
  convertation_error = 1,
  // Ошибка функций округления // Other functions
  calculation_error = 1,
  // дополнительно - ошибка индекса бита
  index_error = -3
};

// массив определен в s21_get_bit, содержит 0 - 31 степень двойки
extern unsigned int powers_of_two[];

// тип данных decimal
typedef struct {
  // тип unsigned int, необходим чтобы
  // при сдаиге вправо >> первый включенный бит
  // принимал значение 0
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  // тип unsigned int, необходим чтобы
  // при сдаиге вправо >> первый включенный бит
  // принимал значение 0
  unsigned int bits[7];
} s21_big_dec;

// Arithmetic operators
int s21_add(s21_decimal, s21_decimal, s21_decimal *);  // +
int s21_sub(s21_decimal, s21_decimal, s21_decimal *);  // -
int s21_mul(s21_decimal, s21_decimal, s21_decimal *);  // *
int s21_div(s21_decimal, s21_decimal, s21_decimal *);  // /

// Comparison Operators
int s21_is_less(s21_decimal, s21_decimal);              // <
int s21_is_less_or_equal(s21_decimal, s21_decimal);     // <=
int s21_is_greater(s21_decimal, s21_decimal);           // >
int s21_is_greater_or_equal(s21_decimal, s21_decimal);  // >=
int s21_is_equal(s21_decimal, s21_decimal);             // ==
int s21_is_not_equal(s21_decimal, s21_decimal);         // !=

// Convertors and parsers
int s21_from_int_to_decimal(int, s21_decimal *);
int s21_from_float_to_decimal(float, s21_decimal *);
int s21_from_decimal_to_int(s21_decimal, int *);
int s21_from_decimal_to_float(s21_decimal, float *);

// Other functions
int s21_floor(s21_decimal, s21_decimal *);
int s21_round(s21_decimal, s21_decimal *);
int s21_truncate(s21_decimal, s21_decimal *);
int s21_negate(s21_decimal, s21_decimal *);

// Common helpers
int s21_set_bit(s21_decimal *, int);  // turn on any bit
int s21_get_bit(s21_decimal *, int);  // show bit condition
unsigned int s21_get_exponent(s21_decimal *);
int s21_set_exponent(s21_decimal *, unsigned char);
int s21_shift_left(s21_decimal *, int);   // <<
int s21_shift_right(s21_decimal *, int);  // >>
int s21_set_bit_off(s21_decimal *, int);
// s21_decimal s21_sum_mantis(s21_decimal num1, s21_decimal num2);
int s21_normalize(s21_decimal *, s21_decimal *);
int s21_mult_ten(s21_decimal *, int);
int s21_in(char, char *);               // is char in string ? Y1/N0
void s21_empty_decimal(s21_decimal *);  // clean decimal - 0 0 0 0
/** scientific notation string to decimal **/
void s21_set_val_from_str(s21_decimal *, char *, int *);
/** get exponent from scientific notation string **/
int s21_get_float_exp_from_string(char *);
void s21_sub_mantiss(s21_decimal *, s21_decimal *);  // -
unsigned int s21_div_mantiss(
    s21_decimal *,
    s21_decimal *);  // division with truncating of remainder
int s21_mant_sum(s21_decimal *, s21_decimal *, s21_decimal *);
int s21_div_cycl(s21_decimal *, s21_decimal *, s21_decimal *);
int s21_div_ten(s21_decimal *, int);  // like truncate
int s21_is_zero(s21_decimal *);
int s21_mul_mant(s21_decimal *, s21_decimal *);
int s21_process_rounding(s21_decimal *, s21_decimal *, s21_decimal *,
                         s21_decimal *);
void s21_PP(s21_decimal *);
int s21_banking_round(s21_decimal *, s21_decimal *);

// from versiebe branch
int s21_is_less_mantis(s21_decimal *d1, s21_decimal *d2);
int s21_compare(s21_decimal *, s21_decimal *);
int s21_is_possible_x10(s21_decimal *);

// for big decimal
int s21_from_dec_to_big(s21_decimal *, s21_big_dec *);
int s21_from_big_to_dec(s21_big_dec *, s21_decimal *);
void s21_print_big(s21_big_dec *);
int s21_is_zero_big(s21_big_dec *);
int s21_get_bit_big(s21_big_dec *, int);
int s21_mant_sum_big(s21_big_dec *, s21_big_dec *, s21_big_dec *);
unsigned int s21_get_exp_big(s21_big_dec *);
int s21_set_exp_big(s21_big_dec *, unsigned char);
int s21_shift_left_big(s21_big_dec *, int);
int s21_shift_right_big(s21_big_dec *, int);
int s21_set_bit_big(s21_big_dec *, int);
int s21_set_bit_off_big(s21_big_dec *, int);
unsigned int s21_div_mantiss_big(s21_big_dec *, s21_big_dec *);
int s21_is_mant_equal_big(s21_big_dec *, s21_big_dec *);
int s21_is_less_mantis_big(s21_big_dec *, s21_big_dec *);
void s21_sub_mantiss_big(s21_big_dec *, s21_big_dec *);
int s21_div_ten_big(s21_big_dec *, int);
int s21_mult_10_big(s21_big_dec *, int);
int s21_mul_mant_big(s21_big_dec *, s21_big_dec *);
#endif  // S21_DECIMAL