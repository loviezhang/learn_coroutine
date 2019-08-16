#include <malloc.h>
#include <stdlib.h>
#include "coroutine.h"

#define STACK_SIZE  (1024 * 1024)

coctx* co_main = NULL;

// 从当前协程切换到其他协程
extern int co_swap(coctx* from, coctx* to) asm("co_swap");

static void co_entry(coctx* ctx, co_func fn, int64_t arg) {
    fn(arg);
    // 标记协程已完成
    ctx->finish = true;
    co_swap(ctx, co_main);
}

coctx* co_create(co_func fn, uint64_t arg) {
    if (co_main == NULL) {
        // 首次调用需创建main函数的协程帧
        co_main = (coctx*)calloc(1, sizeof(coctx));
    }

    coctx* ctx = (coctx*)calloc(1, sizeof(coctx));

    // 16字节对齐
    ctx->ss = (char*)memalign(16, STACK_SIZE);
    ctx->finish = false;

    // 减8的目的是留8字节存放返回地址
	ctx->regs[REG_RSP] = (uint64_t)(ctx->ss + STACK_SIZE - 8);
    // 从co_entry开始执行
	ctx->regs[REG_RIP] = (uint64_t)co_entry;
    // 根据寄存器约定，rdi/rsi/rdx分别存储第一个/第二个/第三个参数
	ctx->regs[REG_RDI] = (uint64_t)ctx;
	ctx->regs[REG_RSI] = (uint64_t)fn;
	ctx->regs[REG_RDX] = arg;

    return ctx;
}

void co_release(coctx* ctx) {
    if (ctx->ss != NULL) {
        free(ctx->ss);
    }
    free(ctx);
}
