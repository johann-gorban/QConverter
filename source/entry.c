#include "entry.h"
#include "logic.h"
#include "errors.h"

#include <stdint.h>

#define TRUE 1
#define FALSE 0

void executeOperation(Operation operation, Context *context) {
    switch (operation) {
        case VALIDATE: {
            context->error_flag = validate_base(context->source_num, context->source_base);
            if (context->error_flag) {
                context->error = INCORRECT_INPUT;
                context->error_message = (char *) get_error_message(context->error);
            }
            break;
        }
        case CHECK_SIZE: {
            context->error_flag = fits_in_32_bits(context->source_num, context->source_base);
            if (context->error_flag) {
                context->error = TOO_LONG_NUM;
                context->error_message = (char *) get_error_message(context->error);
            }
            break;
        }
        case CONVERT: {
            int32_t temp =(int32_t) any_to_dec(context->source_num, context->source_base);
            Error error = dec_to_any(temp, context->final_base, &(context->final_num));
            if (error != NO_ERROR) {
                context->error = error;
                context->error_flag = TRUE;
                context->error_message = (char *) get_error_message(context->error);
            }
            break;
        }
        case CONTEXT_INITIALIZATION: {
            context_init(context);
            break;
        }
        case CONTEXT_CLEAR: {
            context_clear_errors(context);
            break;
        }
        default: {
            context->final_num = "0";
            break;
        }
    }
}
