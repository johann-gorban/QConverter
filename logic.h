#pragma once

#include "context.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Function to convert decimal number to number with the given base
char *dec_to_any(const int, const unsigned int);

// Function to get decimal number by char (base up to 16)
int get_dec_by_char(const char);

// Function to convert number to decimal from any base
int32_t any_to_dec(const char *, const unsigned int);

// Function to validate string as number with the given base
int validate_base(const char *, const unsigned int);

// Context initialization
void context_init(Context *);

// Function to get error message by index
const char *get_error_message(const Error);

#ifdef __cplusplus
}
#endif
