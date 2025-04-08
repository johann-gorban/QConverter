#include "utils.h"

#include "bases.h"
#include "errors.h"

#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_LENGTH 256

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

int str_to_int(const char *str) {
    int num = 0;

    const size_t length = strlen(str);
    for (size_t i = 0; i < length; i++) {
        if (str[i] != '-') {
            unsigned int digit = (int)str[i] - '0';
            num += (int)(digit * pow(DEC_BASE, length - i - 1));
        }
    }

    if (str[0] == '-') {
        num = -1 * num;
    }

    return num;
}

Error int_to_str(const int num, char **buffer) {
    Error error = allocate_memory(buffer, MAX_LENGTH);

    if (error == NO_ERROR) {
        int is_negative = num < 0;
        unsigned int abs_num = is_negative ? -num : num;

        int i = 0;
        do {
            (*buffer)[i++] = '0' + (abs_num % 10);
            abs_num /= 10;
        } while (abs_num > 0 && i < MAX_LENGTH);

        if (is_negative) {
            (*buffer)[i++] = '-';
        }

        (*buffer)[i] = '\0';
        reverse_str(*buffer, *buffer + strlen(*buffer) - 1);
    }
    return error;
}

Error allocate_memory(void *ptr, size_t size) {
    Error error = NO_ERROR;

    ptr = malloc(size);

    if (!ptr) {
        error = MEMORY_ALLOCATION_ERROR;
    }

    return error;
}
