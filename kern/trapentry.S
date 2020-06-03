/* See COPYRIGHT for copyright information. */

#include <inc/mmu.h>
#include <inc/memlayout.h>
#include <inc/trap.h>

#include <kern/picirq.h>


###################################################################
# exceptions/interrupts
###################################################################

/* TRAPHANDLER defines a globally-visible function for handling a trap.
 * It pushes a trap number onto the stack, then jumps to _alltraps.
 * Use TRAPHANDLER for traps where the CPU automatically pushes an error code.
 *
 * You shouldn't call a TRAPHANDLER function from C, but you may
 * need to _declare_ one in C (for instance, to get a function pointer
 * during IDT setup).  You can declare the function with
 *   void NAME();
 * where NAME is the argument passed to TRAPHANDLER.
 */
#define TRAPHANDLER(name, num)						\
	.globl name;		/* define global symbol for 'name' */	\
	.type name, @function;	/* symbol type is function */		\
	.align 2;		/* align function definition */		\
	name:			/* function starts here */		\
	pushl $(num);							\
	jmp _alltraps

/* Use TRAPHANDLER_NOEC for traps where the CPU doesn't push an error code.
 * It pushes a 0 in place of the error code, so the trap frame has the same
 * format in either case.
 */
#define TRAPHANDLER_NOEC(name, num)					\
	.globl name;							\
	.type name, @function;						\
	.align 2;							\
	name:								\
	pushl $0;							\
	pushl $(num);							\
	jmp _alltraps

.text

/*
 * Lab 3: Your code here for generating entry points for the different traps.
 */

TRAPHANDLER_NOEC(ISR0, T_DIVIDE)
TRAPHANDLER_NOEC(ISR1, T_DEBUG)
TRAPHANDLER_NOEC(ISR2, T_NMI)
TRAPHANDLER_NOEC(ISR3, T_BRKPT)
TRAPHANDLER_NOEC(ISR4, T_OFLOW)
TRAPHANDLER_NOEC(ISR5, T_BOUND)
TRAPHANDLER_NOEC(ISR6, T_ILLOP)
TRAPHANDLER_NOEC(ISR7, T_DEVICE)

TRAPHANDLER(ISR8, T_DBLFLT)
TRAPHANDLER(ISR10, T_TSS)
TRAPHANDLER(ISR11, T_SEGNP)
TRAPHANDLER(ISR12, T_STACK)
TRAPHANDLER(ISR13, T_GPFLT)
TRAPHANDLER(ISR14, T_PGFLT)
TRAPHANDLER_NOEC(ISR16, T_FPERR)
TRAPHANDLER(ISR17, T_ALIGN)
TRAPHANDLER_NOEC(ISR18, T_MCHK)
TRAPHANDLER_NOEC(ISR19, T_SIMDERR)

TRAPHANDLER_NOEC(ISR48, T_SYSCALL)
TRAPHANDLER(ISR500, T_DEFAULT)

_alltraps:
	pushl %ds
	pushl %es
	pushal
	mov $(GD_KD), %ax
	mov %ax, %ds
	mov %ax, %es
	pushl %esp
	call trap
	addl $4, %esp
	popal
	pop %es
	pop %ds
	addl $8, %esp
	iret

/*
 * Lab 3: Your code here for _alltraps
 */

