#include "logic.h"

#include "utils.h"
#include "errors.h"
#include "bases.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

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

int validate_base(const char *str, const unsigned int base) {
    int result = TRUE;
    for (size_t i = 0; i < strlen(str); i++) {
        if (base == DEC_BASE && str[0] == '-'){
            continue;
        }
        int digit = get_dec_by_char(str[i]);
        if (digit < 0 || digit >= base) {
            result = FALSE;
        }
    }
    return result;
}

char *dec_to_any(const int32_t num, const unsigned int base) {
    char *result = NULL;

    int ok = 1;

    char *buffer = (char *)malloc(MAX_BITS + 3);  // +1 знак, +1 \0
    if (!buffer || base < MIN_BASE || base > MAX_BASE) {
        ok = 0;
    }

    else {
        int i = 0;
        if (base != DEC_BASE) {
            uint32_t val = (uint32_t)num;
            do {
                buffer[i++] = DIGITS_CHAR[val % base];
                val /= base;
            } while (val);

            buffer[i] = '\0';
            reverse_str(buffer, buffer + i - 1);
            result = buffer;
        }
        else {
            result = int_to_str(num);
        }
    }

    if (!ok && buffer) free(buffer);
    return result;
}

int32_t any_to_dec(const char *str, const unsigned int base) {
    int32_t result = 0;
    if (validate_base(str, base)) {
        // Process decimal number
        if (base == DEC_BASE) {
            int sign = 1;
            size_t i = 0;

            if (str[0] == '-') {
                sign = -1;
                i = 1;
            }

            for (; str[i]; ++i) {
                result = result * DEC_BASE + get_dec_by_char(str[i]);
            }

            result *= sign;
        }
        // Process two's complement
        else {
            uint32_t unsigned_result = 0;
            for (size_t i = 0; str[i]; ++i) {
                unsigned_result = unsigned_result * base + get_dec_by_char(str[i]);
            }
            result = (int32_t) unsigned_result;
        }
    }

    return result;
}

void context_init(Context *context) {
    context->source_num = (char *)"0\0";
    context->source_base = 2;
    context->final_num = (char *)"0\0";
    context->final_base = 2;
    context->error_flag = FALSE;
    context->error = -1;
}
