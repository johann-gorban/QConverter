#include "logic.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

const char DIGITS_CHAR[] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F'
};

unsigned int get_dec_by_char(const char digit) {
    unsigned int res = 0;
    switch (digit) {
    // Default digits
    case '0': res = 0; break;
    case '1': res = 1; break;
    case '2': res = 2; break;
    case '3': res = 3; break;
    case '4': res = 4; break;
    case '5': res = 5; break;
    case '6': res = 6; break;
    case '7': res = 7; break;
    case '8': res = 8; break;
    case '9': res = 9; break;

        // Upper case
    case 'A': res = 10; break;
    case 'B': res = 11; break;
    case 'C': res = 12; break;
    case 'D': res = 13; break;
    case 'E': res = 14; break;
    case 'F': res = 15; break;

    // Lower case
    case 'a': res = 10; break;
    case 'b': res = 11; break;
    case 'c': res = 12; break;
    case 'd': res = 13; break;
    case 'e': res = 14; break;
    case 'f': res = 15; break;

    default: res = 0; break;
    }
    return res;
}

int validate_base(const char *str, const unsigned int base) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (base == 10 && str[0] == '-'){
            continue;
        }
        if (get_dec_by_char(str[i]) >= base) {
            return FALSE;
        }
    }
    return TRUE;
}

char *reverse_str(const char *str) {
    if (!str) {
        return NULL;
    }

    size_t length = strlen(str);
    char *reversed_str = (char *)calloc(length, sizeof(char));

    for (size_t i = length; i != 0; i--) {
        reversed_str[length - i] = str[i - 1];
    }

    return reversed_str;
}

char *dec_to_any(const int num, const unsigned int base) {
    if (base > 16 || base < 2) {
        return NULL;
    }

    char *str = (char *)malloc(sizeof(char) * 65);
    str[0] = '\0';

    int coef = (num < 0 && base == 10) ? -1 : 1;

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

    return reverse_str(str);
}

int any_to_dec(const char *str, const unsigned int base) {
    int result = 0;

    if (validate_base(str, base)) {
        size_t length = strlen(str);

        for (size_t i = length; i != 0; i--) {
            result += get_dec_by_char(str[length - i]) * pow(base, i - 1);
        }
    }

    return result;
}

int str_to_int(const char *str) {
    int num = 0;

    if (validate_base(str, 10)) {
        const size_t length = strlen(str);
        for (size_t i = 0; i < length; i++) {
            if (str[i] != '-') {
                unsigned int digit = (int)str[i] - '0';
                num += (int)(digit * pow(10, length - i - 1));
            }
        }

        if (str[0] == '-') {
            num = (-1) * num;
        }
    }
    return num;
}
