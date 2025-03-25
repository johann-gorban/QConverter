#include "entry.h"


void executeOperation(Operation operation, Context *contex, AppContext *app_context) {
    switch (operation) {
    case DecToAny:
        int num = str_to_int(context->num);
        context->num = dec_to_any(num, app_context->base_to);
        break;
    case AnyToDec:
        int num = any_to_dec(context->num, app_context->base_to);
        context->num = dec_to_any(num, 10);
        break;
    }
}
