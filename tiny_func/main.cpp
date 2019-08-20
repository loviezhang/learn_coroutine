#include <stdio.h>

int func2(int a, int b) {
    int c = a + b;
    return c;
}

int func1(int a) {
    int x = 2;
    int d = func2(a, x);
    return d;
}

int main(int argc, char** argv) {
    return func1(1);
}
