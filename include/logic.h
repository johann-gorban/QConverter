#pragma once

#include "context.h"

#include <stdint.h>
#include "errors.h"

#ifdef __cplusplus
extern "C" {
#endif

// Function to convert decimal number to number with the given base
Error dec_to_any(const int32_t num, const unsigned int base, char **buffer);

// Function to get decimal number by char (base up to 16)
int get_dec_by_char(const char);

// Function to convert number to decimal from any base
long long any_to_dec(const char *, const unsigned int);

// Function to validate string as number with the given base
int validate_base(const char *, const unsigned int);

// Context initialization
void context_init(Context *);

void context_clear_errors(Context *);

// Function to get error message by index
const char *get_error_message(const Error);

// Check the size of the number
int fits_in_32_bits(const char *, const unsigned);

#ifdef __cplusplus
}
#endif
