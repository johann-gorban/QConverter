#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char *source_num;
    unsigned int source_base;

    char *final_num;
    unsigned int final_base;
} Context;

#ifdef __cplusplus
}
#endif
