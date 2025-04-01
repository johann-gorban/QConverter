#include "logic.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

#define BIN_BASE 2
#define OCT_BASE 8
#define DEC_BASE 10
#define HEX_BASE 16

#define MAX_BITS 32

#define MAX_BASE   16
#define MIN_BASE    2

const char DIGITS_CHAR[] = "0123456789ABCDEF";

int get_dec_by_char(const char digit) {
    int res = -1;

    if (isdigit(digit)) {
        res = digit - '0';
    }
    if (isupper(digit)){
        res = digit - 'A' + 10;
    }
    if (islower(digit)) {
        res = digit - 'a' + 10;
    }

    return res;
}

// Декомпозировать, убрать множественные ретурны
int fits_in_32_bits(const char *str, unsigned int base) {
    int result = TRUE;
    if (base < MIN_BASE || base > MAX_BASE)
        result = FALSE;

    if (!validate_base(str, base)) {
        result = FALSE;
    }

    uint32_t max_val = UINT32_MAX;
    if (base == DEC_BASE && str[0] == '-') {
            max_val = UINT16_MAX;
    }

    uint32_t value = 0;
    uint32_t max_div_base = max_val / base;

    for (const char *p = str; *p != '\0'; p++) {
        int digit = get_dec_by_char(*p);

        if (value > max_div_base) result = FALSE;

        value *= base;

        if (value > max_val - digit) result = FALSE;

        value += digit;
    }

    return result;
}

int validate_base(const char *str, const unsigned int base) {
    int result = TRUE;
    for (size_t i = 0; i < strlen(str); i++) {
        if (base == DEC_BASE && str[0] == '-'){
            continue;
        }
        int digit = get_dec_by_char(str[i]);
        if (digit >= base || digit < 0) {
            result = FALSE;
        }
    }
    return result;
}

char *dec_to_any(const int num, const unsigned int base) {
    if (base > MAX_BASE || base < MIN_BASE) {
        return NULL;
    }

    // decompose and check whether it returns nullptr
    char *str = (char *)malloc(sizeof(char) * (MAX_BITS + 1));
    str[0] = '\0';

    int coef = (num < 0 && base == DEC_BASE) ? -1 : 1;

    int cpy_num = coef * num;
    do {
        char digit[2];
        digit[0] = DIGITS_CHAR[cpy_num % base];
        digit[1] = '\0';

        strcat(str, digit);
        cpy_num /= base;
    } while (cpy_num);

    if (coef == -1) {
        strcat(str, "-\0");
    }

    reverse_str(str, str + strlen(str) - 1);

    return str;
}

int any_to_dec(const char *str, const unsigned int base) {
    int result = 0;

    if (validate_base(str, base) && fits_in_32_bits(str, base)) {
        size_t length = strlen(str);

        for (size_t i = length; i != 0; i--) {
            result += get_dec_by_char(str[length - i]) * pow(base, i - 1);
        }
    }

    return result;
}

int str_to_int(const char *str) {
    int num = 0;

    if (validate_base(str, DEC_BASE)) {
        const size_t length = strlen(str);
        for (size_t i = 0; i < length; i++) {
            if (str[i] != '-') {
                unsigned int digit = (int)str[i] - '0';
                num += (int)(digit * pow(DEC_BASE, length - i - 1));
            }
        }

        if (str[0] == '-') {
            num = (-1) * num;
        }
    }
    return num;
}
