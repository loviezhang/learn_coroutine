#include <stdio.h>
#include "coroutine.h"

coctx* co_func1;
coctx* co_func2;

void func1(uint64_t arg) {
    int a = 10;
    printf("func1: befor co_swap, arg = %lu, a = %d\n", arg, a);
    co_swap(co_func1, co_func2);
    printf("func1: after co_swap, arg = %lu, a = %d\n", arg, a);
}

void func2(uint64_t arg) {
    int a = 20;
    printf("func2: befor co_swap, arg = %lu, a = %d\n", arg, a);
    co_swap(co_func2, co_func1);
    printf("func2: after co_swap, arg = %lu, a = %d\n", arg, a);
}

int main(int argc, char** argv) {
    co_func1 = co_create(func1, 10);
    co_func2 = co_create(func2, 20);

    co_swap(co_main, co_func1);

    co_release(co_func1);
    co_release(co_func2);

    return 0;
}
