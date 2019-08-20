#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "coroutine.h"

#define STACK_SIZE  (1024 * 1024)

coctx* co_main = NULL;
char* co_stack = NULL;

extern int coctx_swap(coctx* from, coctx* to) asm("coctx_swap");

static void co_entry(coctx* ctx, co_func fn, uint64_t arg) {
    fn(arg);
    // 标记协程已完成
    ctx->finish = true;
    // 切回主协程
    co_swap(ctx, co_main);
}

coctx* co_create(co_func fn, uint64_t arg) {
    if (co_main == NULL) {
        // 首次调用需创建主协程的协程帧
        co_main = (coctx*)calloc(1, sizeof(coctx));
        co_main->main = true;
    }
    if (co_stack == NULL) {
        // 创建共享栈
        co_stack = (char*)memalign(16, STACK_SIZE);
    }

    coctx* ctx = (coctx*)calloc(1, sizeof(coctx));

    ctx->stack_save = NULL;
    ctx->stack_save_size = 0;

    ctx->finish = false;
    ctx->main = false;

    // 减8的目的是留8字节存放返回地址
	ctx->regs[REG_RSP] = (uint64_t)(co_stack + STACK_SIZE - 8);
    // 从co_entry开始执行
	ctx->regs[REG_RIP] = (uint64_t)co_entry;
    // 根据寄存器约定，rdi/rsi/rdx分别存储第一个/第二个/第三个参数
	ctx->regs[REG_RDI] = (uint64_t)ctx;
	ctx->regs[REG_RSI] = (uint64_t)fn;
	ctx->regs[REG_RDX] = arg;

    return ctx;
}

// 从当前协程切换到其他协程
void co_swap(coctx* from, coctx* to) {
    // 第一个变量位于栈顶，通过这个方式获取栈顶地址
    char top_of_stack = 0;
    char* stack_sp = &top_of_stack;

    // 存到静态变量中，防止栈被覆盖后无法读取
    static coctx* co_to;
    co_to = to;

    if (!from->main) {
        // 备份协程栈
        from->stack_save_size =
            (size_t)(co_stack + STACK_SIZE) - (size_t)stack_sp;
        if (from->stack_save) {
            free(from->stack_save);
        }
        from->stack_save = malloc(from->stack_save_size);
        memcpy(from->stack_save, stack_sp, from->stack_save_size);
    }

    // 协程切换
    coctx_swap(from, to);

    if (co_to->stack_save != NULL) {
        // 恢复协程的栈
        memcpy(co_stack + STACK_SIZE - co_to->stack_save_size,
                co_to->stack_save, co_to->stack_save_size);
    }
}

void co_release(coctx* ctx) {
    if (ctx->stack_save != NULL) {
        free(ctx->stack_save);
    }
    free(ctx);
}
