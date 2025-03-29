#include "entry.h"
#include "logic.h"

void executeOperation(Operation operation, Context *context) {
    int temp = 0;
    switch (operation) {
    case convert:
        if (context->source_base != 10){
            temp = any_to_dec(context->source_num, context->source_base);
        }
        else {
            temp = str_to_int(context->source_num);
        }
        context->final_num = dec_to_any(temp, context->final_base);
        break;
    default:
        context->final_num = "0";
        break;
    }
}
