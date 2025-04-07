#include "entry.h"
#include "logic.h"

#include <stdint.h>

void executeOperation(Operation operation, Context *context) {
    int32_t temp = 0;
    switch (operation) {
    case convert:
        temp = any_to_dec(context->source_num, context->source_base);
        context->final_num = dec_to_any(temp, context->final_base);
        break;
    case context_initialization:
        context_init(context);
        break;
    default:
        context->final_num = "0";
        break;
    }
}
