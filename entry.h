#pragma once

#include "context.h"
#include "logic.h"

#ifdef __cplusplus
extern "C" {
#endif

// Available operations
enum Operation {
    DecToAny
    AnyToDec;
};

// Application params
typedef struct {
    unsigned int base_to;
} AppContext;

// Main function to execute operations (other functions)
void executeOperation(Operation, Context*, AppContext*);

#ifdef __cplusplus
}
#endif
