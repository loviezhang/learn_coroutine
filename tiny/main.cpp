#include <stdio.h>
#include "coroutine.h"

int func(int p) {
    return 0;
}

int co_func(int p) {
    return 0;
}

int main(int argc, char** argv) {
    int ret = 0;

    ret = func(2);

    /*
    co_context* ctx = co_create(co_func);
    co_resume(ctx);

    co_destroy(ctx);
    */

    return 0;
}
