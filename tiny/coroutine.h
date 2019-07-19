#pragma once

#define CO_STACK_SIZE   (4 * 1024 * 1024)

struct co_context {
};

co_context* co_create(int(*)(int));
void co_resume(co_context* ctx);
void co_yield();
void co_destroy(co_context* ctx);
