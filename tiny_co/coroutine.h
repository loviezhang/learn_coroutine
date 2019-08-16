#pragma once

#include <stdint.h>

enum {
    REG_RDI = 7,
    REG_RSI = 8,
    REG_RIP = 9,
    REG_RDX = 10,
    REG_RSP = 13,
};

struct coctx {
    // 内存结构：
    // low | regs[0]:  r15 |
    //     | regs[1]:  r14 |
    //     | regs[2]:  r13 |
    //     | regs[3]:  r12 |
    //     | regs[4]:  r9  |
    //     | regs[5]:  r8  | 
    //     | regs[6]:  rbp |
    //     | regs[7]:  rdi |
    //     | regs[8]:  rsi |
    //     | regs[9]:  rip |
    //     | regs[10]: rdx |
    //     | regs[11]: rcx | 
    //     | regs[12]: rbx |
    // hig | regs[13]: rsp |
    //
    // 注：根据寄存器约定，rax为返回值，不用备份
    //     r10/r11为调用者保护，也不用备份
    uint64_t regs[14];

    char* ss;

    bool finish;
};

extern coctx* co_main;

typedef void (*co_func)(uint64_t arg);

// 创建一个协程，创建后处于挂起状态
coctx* co_create(co_func fn, uint64_t arg);

void co_release(coctx* ctx);

// 协程切换
extern int co_swap(coctx* from, coctx* to) asm("co_swap");
