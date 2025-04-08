#pragma once

#ifndef NUMBER_TOO_LONG_MSG
#define NUMBER_TOO_LONG_MSG "The input number is too long"
#endif

#ifndef INCORRECT_CHARS_MSG
#define INCORRECT_CHARS_MSG "The input number is incorrect"
#endif

#ifndef MEMORY_ALLOCATION_ERROR_MSG
#define MEMORY_ALLOCATION_ERROR_MSG "Memory allocation problems"
#endif

#ifndef NO_ERROR_MSG
#define NO_ERROR_MSG "No errors"
#endif

#ifndef UNKNOWN_ERROR_MSG
#define UNKNOWN_ERROR_MSG "Unknown error"
#endif

#ifndef WRONG_BASE_MSG
#define WRONG_BASE_MSG "Wrong base"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NO_ERROR,
    TOO_LONG_NUM,
    INCORRECT_INPUT,
    WRONG_BASE,
    MEMORY_ALLOCATION_ERROR
} Error;

#ifdef __cplusplus
}
#endif
