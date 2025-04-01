#include "logic.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <limits.h>

#define TRUE 1
#define FALSE

#define BIN_BASE 2
#define OCT_BASE 8
#define DEC_BASE 10
#define HEX_BASE 16

#define MAX_BITS 32

#define MAX_BASE   HEX_BASE
#define MIN_BASE    BIN_BASE

const char DIGITS_CHAR[] = "0123456789ABCDEF";

unsigned int get_dec_by_char(const char digit) {
    unsigned int res = 0;

    if (isdigit(digit)) {
        res = digit - '0';
    } else if (isupper(digit)){
        res = digit - 'A';
    } else if (islower(digit)) {
        res = digit - 'a';
    }

    return res;
}

// Декомпозировать, убрать множественные ретурны
int fits_in_32_bits(const char* str, unsigned int base) {
    if (base < MIN_BASE || base > MAX_BASE)
        return 0;

    int is_negative = 0;
    const char* num_start = str;

    if (*num_start == '-') {
        if (base != 10) return 0;
        is_negative = 1;
        num_start++;
    } else if (*num_start == '+') {
        num_start++;
    }

    if (*num_start == '\0') return 0;

    uint32_t max_val;
    if (base == 10) {
        if (is_negative) {
            max_val = UINT16_MAX;
        } else {
            max_val = INT32_MAX;
        }
    } else {
        max_val = UINT32_MAX;
    }

    uint32_t value = 0;
    uint32_t max_div_base = max_val / base;

    for (const char* p = num_start; *p != '\0'; p++) {
        if (*p == '-' && base != DEC_BASE) {
            is_negative = 1;
            continue;
        }

        int digit;
        if (isdigit(*p)) {
            digit = *p - '0';
        } else if (isupper(*p)) {
            digit = *p - 'A' + 10;
        } else if (islower(*p)) {
            digit = *p - 'a' + 10;
        } else {
            return 0;  // Недопустимый символ
        }

        if (digit >= base) return 0;

        if (value > max_div_base) return 0;
        value *= base;

        if (value > max_val - digit) return 0;
        value += digit;
    }

    if (is_negative && base != DEC_BASE) {
        if (value > UINT16_MAX) return 0;
    }

    return 1;
}

int validate_base(const char *str, const unsigned int base) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (base == DEC_BASE && str[0] == '-'){
            continue;
        }
        if (get_dec_by_char(str[i]) >= base) {
            return FALSE;
        }
    }
    return TRUE;
}

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void reverse_str(char *start, char *end) {
    while (start < end) {
        swap(start, end);
        start++;
        end--;
    }
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

    if (validate_base(str, DEC_BASE) && fits_in_32_bits(str, DEC_BASE)) {
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
