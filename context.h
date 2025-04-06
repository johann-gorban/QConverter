#pragma once

#include "errors.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char *source_num;
    unsigned int source_base;

    char *final_num;
    unsigned int final_base;

    int error_flag;
    Error error;
} Context;

#ifdef __cplusplus
}
#endif
