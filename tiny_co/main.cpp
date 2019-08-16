#include <stdio.h>
#include "coroutine.h"

coctx* co_func1;

void func1(uint64_t arg) {
    printf("step1 in func1, arg %lu\n", arg);
    co_swap(co_func1, co_main);
    printf("step2 in func1, arg %lu\n", arg);
}

int main(int argc, char** argv) {
    co_func1 = co_create(func1, 10);

    do {
        printf("swap co_func\n");
        co_swap(co_main, co_func1);
    } while (!co_func1->finish);

    printf("co_func finish\n");
    co_release(co_func1);

    return 0;
}
