.globl coctx_swap
.type  coctx_swap, @function

// int coctx_swap(coctx* from, coctx* to)
coctx_swap:
	leaq 8(%rsp), %rax   // rax = rsp + 8，也就是去除返回地址后原始的rsp
	leaq 112(%rdi), %rsp // rdi + 112 = &(from->regs[14])，这是是让rsp执行from->regs的结尾
	pushq %rax           // from->regs[13] = rsp
	pushq %rbx           // from->regs[12] = rbx
	pushq %rcx           // from->regs[11] = rcx
	pushq %rdx           // from->regs[10] = rcx

	pushq -8(%rax)       // rax-8指向返回地址，也就是 from->regs[9] = 返回地址

	pushq %rsi           // from->regs[8] = rsi
	pushq %rdi           // from->regs[7] = rdi
	pushq %rbp           // from->regs[6] = rbp
	pushq %r8            // from->regs[5] = r8
	pushq %r9            // from->regs[4] = r9
	pushq %r12           // from->regs[3] = r12
	pushq %r13           // from->regs[2] = r13
	pushq %r14           // from->regs[1] = r14
	pushq %r15           // from->regs[0] = r15
	
	movq %rsi, %rsp      // rsp = &to->regs[0]
	popq %r15            // r15 = to->regs[0]
	popq %r14            // r14 = to->regs[1]
	popq %r13            // r13 = to->regs[2]
	popq %r12            // r12 = to->regs[3]
	popq %r9             // r9  = to->regs[4]
	popq %r8             // r8  = to->regs[5]
	popq %rbp            // rbp = to->regs[6]
	popq %rdi            // rdi = to->regs[7]
	popq %rsi            // rsi = to->regs[8]
	popq %rax            // rax = to->regs[9]，把返回地址存入rax
	popq %rdx            // rdx = to->regs[10]
	popq %rcx            // rcx = to->regs[11]
	popq %rbx            // rbx = to->regs[12]
	popq %rsp            // rsp = to->regs[13]，栈已恢复
	pushq %rax           // 把返回地址压栈，以便ret指令返回时用
	
	xorl %eax, %eax      // rax存储返回值，这里把返回值置为0
	ret                  // pop返回地址，并jmp返回地址
