#include "utils.h"

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
