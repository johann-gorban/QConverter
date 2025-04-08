#include "logic.h"

#include "utils.h"
#include "errors.h"
#include "bases.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define OK 0
#define ERROR 1

#define MAX_LENGTH 256

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
    int result = OK;
    for (size_t i = 0; i < strlen(str); i++) {
        if (base == DEC_BASE && str[0] == '-'){
            continue;
        }
        int digit = get_dec_by_char(str[i]);
        if (digit < 0 || (unsigned int) digit >= base) {
            result = ERROR;
        }
    }
    return result;
}

int fits_in_32_bits(const char *str, const unsigned base) {
    int result = OK;
    long long intValue = any_to_dec(str, base);

    if (intValue > INT32_MAX || intValue < INT32_MIN) {
        result = ERROR;
    }
    else if (get_dec_by_char(str[0]) == -1 || str[0] != '-') {
        size_t len = strlen(str);
        for (size_t i = 1; i < len; i++) {
            if (get_dec_by_char(str[i]) == -1) {
                result = ERROR;
                break;
            }
        }
    }
    if (get_dec_by_char(str[0]) == -1 && str[0] != '-') {
        result = ERROR;
    }
    return result;
}

Error dec_to_any(const int32_t num, const unsigned int base, char **buffer) {
    Error error = allocate_memory(buffer, MAX_BITS);
    if (error == NO_ERROR && base <= MAX_BASE && base >= MIN_BASE) {
        int i = 0;
        if (base != DEC_BASE) {
            uint32_t val = (uint32_t)num;
            do {
                (*buffer)[i++] = DIGITS_CHAR[val % base];
                val /= base;
            } while (val);

            (*buffer)[i] = '\0';
            reverse_str(*buffer, *buffer + i - 1);
        }
        else {
            error = int_to_str(num, buffer);
        }
    }
    else {
        error = WRONG_BASE;
    }

    return error;
}

long long any_to_dec(const char *str, const unsigned int base) {
    long long result = 0;
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
            long long unsigned_result = 0;
            for (size_t i = 0; str[i]; ++i) {
                unsigned_result = unsigned_result * base + get_dec_by_char(str[i]);
            }
            result = (long long) unsigned_result;
        }

    return result;
}

void context_init(Context *context) {
    context->source_num = (char *) malloc(MAX_LENGTH);
    if (context->source_num) {
        context->source_num[0] = '0';
        context->source_num[1] = '\0';
    }
    context->source_base = 2;

    context->final_num = (char *) malloc(MAX_LENGTH);
    if (context->final_num) {
        context->final_num[0] = '0';
        context->final_num[1] = '\0';
    }
    context->final_base = 2;

    context->error = OK;
    context->error_flag = FALSE;
    context->error_message = NULL;
}

void context_clear_errors(Context *context) {
    context->error_flag = OK;
}

const char *get_error_message(const Error error) {
    const char *error_message = NULL;

    switch (error) {
    case NO_ERROR:
        error_message = NO_ERROR_MSG;
        break;
    case TOO_LONG_NUM:
        error_message = NUMBER_TOO_LONG_MSG;
        break;
    case INCORRECT_INPUT:
        error_message = INCORRECT_CHARS_MSG;
        break;
    case MEMORY_ALLOCATION_ERROR:
        error_message = MEMORY_ALLOCATION_ERROR_MSG;
        break;
    case WRONG_BASE:
        error_message = WRONG_BASE_MSG;
        break;
    default:
        error_message = UNKNOWN_ERROR_MSG;
        break;
    }

    return error_message;
}
