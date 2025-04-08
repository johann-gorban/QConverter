#pragma once

#include <stdlib.h>
#include "errors.h"

#ifdef __cplusplus
extern "C" {
#endif

// Function to reverse the string
void reverse_str(char *, char *);

// Swap char function
void swap(char *, char *);

// Function to convert an integer to string
Error int_to_str(const int, char **);

// Function to convert string to integer
int str_to_int(const char *);

// Allocate memory and check errors
Error allocate_memory(void *, size_t);

#ifdef __cplusplus
}
#endif
