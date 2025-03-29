#pragma once

#include "context.h"

#ifdef __cplusplus
extern "C" {
#endif

// Available operations
typedef enum {
    convert
} Operation;

// Main function to execute operations (other functions)
void executeOperation(Operation, Context*);

#ifdef __cplusplus
}
#endif

