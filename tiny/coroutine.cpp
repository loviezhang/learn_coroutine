#include <stdlib.h>
#include <string.h>
#include "coroutine.h"

co_context* g_ctx = NULL;

co_context* co_create(int(*routine)(int)) {
    return NULL;
}

void co_resume(co_context* ctx) {
}

void co_yield() {
}

void co_destroy(co_context* ctx) {
}
