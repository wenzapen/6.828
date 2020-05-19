	.file	"init.c"
	.stabs	"kern/init.c",100,0,2,.Ltext0
	.text
.Ltext0:
	.stabs	"gcc2_compiled.",60,0,0,0
	.stabs	"int:t(0,1)=r(0,1);-2147483648;2147483647;",128,0,0,0
	.stabs	"char:t(0,2)=r(0,2);0;127;",128,0,0,0
	.stabs	"long int:t(0,3)=r(0,3);-2147483648;2147483647;",128,0,0,0
	.stabs	"unsigned int:t(0,4)=r(0,4);0;4294967295;",128,0,0,0
	.stabs	"long unsigned int:t(0,5)=r(0,5);0;4294967295;",128,0,0,0
	.stabs	"__int128:t(0,6)=r(0,6);0;-1;",128,0,0,0
	.stabs	"__int128 unsigned:t(0,7)=r(0,7);0;-1;",128,0,0,0
	.stabs	"long long int:t(0,8)=r(0,8);-9223372036854775808;9223372036854775807;",128,0,0,0
	.stabs	"long long unsigned int:t(0,9)=r(0,9);0;-1;",128,0,0,0
	.stabs	"short int:t(0,10)=r(0,10);-32768;32767;",128,0,0,0
	.stabs	"short unsigned int:t(0,11)=r(0,11);0;65535;",128,0,0,0
	.stabs	"signed char:t(0,12)=r(0,12);-128;127;",128,0,0,0
	.stabs	"unsigned char:t(0,13)=r(0,13);0;255;",128,0,0,0
	.stabs	"float:t(0,14)=r(0,1);4;0;",128,0,0,0
	.stabs	"double:t(0,15)=r(0,1);8;0;",128,0,0,0
	.stabs	"long double:t(0,16)=r(0,1);12;0;",128,0,0,0
	.stabs	"_Float32:t(0,17)=r(0,1);4;0;",128,0,0,0
	.stabs	"_Float64:t(0,18)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Float128:t(0,19)=r(0,1);16;0;",128,0,0,0
	.stabs	"_Float32x:t(0,20)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Float64x:t(0,21)=r(0,1);12;0;",128,0,0,0
	.stabs	"void:t(0,22)=(0,22)",128,0,0,0
	.stabs	"./inc/stdio.h",130,0,0,0
	.stabs	"./inc/stdarg.h",130,0,0,0
	.stabs	"va_list:t(2,1)=(2,2)=*(0,2)",128,0,0,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabs	"./inc/string.h",130,0,0,0
	.stabs	"./inc/types.h",130,0,0,0
	.stabs	"bool:t(4,1)=(4,2)=eFalse:0,True:1,;",128,0,0,0
	.stabs	" :T(4,3)=efalse:0,true:1,;",128,0,0,0
	.stabs	"int8_t:t(4,4)=(0,12)",128,0,0,0
	.stabs	"uint8_t:t(4,5)=(0,13)",128,0,0,0
	.stabs	"int16_t:t(4,6)=(0,10)",128,0,0,0
	.stabs	"uint16_t:t(4,7)=(0,11)",128,0,0,0
	.stabs	"int32_t:t(4,8)=(0,1)",128,0,0,0
	.stabs	"uint32_t:t(4,9)=(0,4)",128,0,0,0
	.stabs	"int64_t:t(4,10)=(0,8)",128,0,0,0
	.stabs	"uint64_t:t(4,11)=(0,9)",128,0,0,0
	.stabs	"intptr_t:t(4,12)=(4,8)",128,0,0,0
	.stabs	"uintptr_t:t(4,13)=(4,9)",128,0,0,0
	.stabs	"physaddr_t:t(4,14)=(4,9)",128,0,0,0
	.stabs	"ppn_t:t(4,15)=(4,9)",128,0,0,0
	.stabs	"size_t:t(4,16)=(4,9)",128,0,0,0
	.stabs	"ssize_t:t(4,17)=(4,8)",128,0,0,0
	.stabs	"off_t:t(4,18)=(4,8)",128,0,0,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"entering test_backtrace %d\n"
.LC1:
	.string	"leaving test_backtrace %d\n"
	.text
	.align 16
	.stabs	"test_backtrace:F(0,22)",36,0,0,test_backtrace
	.stabs	"x:p(0,1)",160,0,0,16
	.globl	test_backtrace
	.type	test_backtrace, @function
test_backtrace:
	.stabn	68,0,13,.LM0-.LFBB1
.LM0:
.LFBB1:
.LFB0:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	subl	$16, %esp
	.cfi_def_cfa_offset 24
	.stabn	68,0,13,.LM1-.LFBB1
.LM1:
	movl	24(%esp), %ebx
	.stabn	68,0,14,.LM2-.LFBB1
.LM2:
	pushl	%ebx
	.cfi_def_cfa_offset 28
	pushl	$.LC0
	.cfi_def_cfa_offset 32
	call	cprintf
	.stabn	68,0,15,.LM3-.LFBB1
.LM3:
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	testl	%ebx, %ebx
	jle	.L2
	.stabn	68,0,16,.LM4-.LFBB1
.LM4:
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	leal	-1(%ebx), %eax
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	test_backtrace
	addl	$16, %esp
	.cfi_def_cfa_offset 16
.L3:
	.stabn	68,0,19,.LM5-.LFBB1
.LM5:
	subl	$8, %esp
	.cfi_def_cfa_offset 24
	pushl	%ebx
	.cfi_def_cfa_offset 28
	pushl	$.LC1
	.cfi_def_cfa_offset 32
	call	cprintf
	.stabn	68,0,20,.LM6-.LFBB1
.LM6:
	addl	$24, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.align 16
.L2:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -8
	.stabn	68,0,18,.LM7-.LFBB1
.LM7:
	subl	$4, %esp
	.cfi_def_cfa_offset 20
	pushl	$0
	.cfi_def_cfa_offset 24
	pushl	$0
	.cfi_def_cfa_offset 28
	pushl	$0
	.cfi_def_cfa_offset 32
	call	mon_backtrace
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	jmp	.L3
	.cfi_endproc
.LFE0:
	.size	test_backtrace, .-test_backtrace
	.stabs	"x:r(0,1)",64,0,0,3
.Lscope1:
	.section	.rodata.str1.1
.LC2:
	.string	"6828 decimal is %o octal!\n"
.LC3:
	.string	"H%x Wo%s\n"
.LC4:
	.string	"x=%d y=%d\n"
	.text
	.align 16
	.stabs	"i386_init:F(0,22)",36,0,0,i386_init
	.globl	i386_init
	.type	i386_init, @function
i386_init:
	.stabn	68,0,24,.LM8-.LFBB2
.LM8:
.LFBB2:
.LFB1:
	.cfi_startproc
	.stabn	68,0,30,.LM9-.LFBB2
.LM9:
	movl	$end, %eax
	.stabn	68,0,24,.LM10-.LFBB2
.LM10:
	subl	$32, %esp
	.cfi_def_cfa_offset 36
	.stabn	68,0,30,.LM11-.LFBB2
.LM11:
	subl	$edata, %eax
	.stabn	68,0,30,.LM12-.LFBB2
.LM12:
	pushl	%eax
	.cfi_def_cfa_offset 40
	pushl	$0
	.cfi_def_cfa_offset 44
	pushl	$edata
	.cfi_def_cfa_offset 48
	call	memset
	.stabn	68,0,34,.LM13-.LFBB2
.LM13:
	call	cons_init
	.stabn	68,0,36,.LM14-.LFBB2
.LM14:
	popl	%eax
	.cfi_def_cfa_offset 44
	popl	%edx
	.cfi_def_cfa_offset 40
	pushl	$6828
	.cfi_def_cfa_offset 44
	pushl	$.LC2
	.cfi_def_cfa_offset 48
	call	cprintf
	.stabn	68,0,38,.LM15-.LFBB2
.LM15:
	movl	$6581362, 28(%esp)
	.stabn	68,0,39,.LM16-.LFBB2
.LM16:
	addl	$12, %esp
	.cfi_def_cfa_offset 36
	leal	16(%esp), %eax
	pushl	%eax
	.cfi_def_cfa_offset 40
	pushl	$57616
	.cfi_def_cfa_offset 44
	pushl	$.LC3
	.cfi_def_cfa_offset 48
	call	cprintf
	.stabn	68,0,40,.LM17-.LFBB2
.LM17:
	popl	%ecx
	.cfi_def_cfa_offset 44
	popl	%eax
	.cfi_def_cfa_offset 40
	pushl	$3
	.cfi_def_cfa_offset 44
	pushl	$.LC4
	.cfi_def_cfa_offset 48
	call	cprintf
	.stabn	68,0,43,.LM18-.LFBB2
.LM18:
	movl	$5, (%esp)
	call	test_backtrace
	addl	$16, %esp
	.cfi_def_cfa_offset 32
	.align 16
.L7:
	.stabn	68,0,47,.LM19-.LFBB2
.LM19:
	subl	$12, %esp
	.cfi_def_cfa_offset 44
	pushl	$0
	.cfi_def_cfa_offset 48
	call	monitor
	addl	$16, %esp
	.cfi_def_cfa_offset 32
	jmp	.L7
	.cfi_endproc
.LFE1:
	.size	i386_init, .-i386_init
	.stabs	"i:(0,4)",128,0,0,12
	.stabn	192,0,0,.LFBB2-.LFBB2
	.stabn	224,0,0,.Lscope2-.LFBB2
.Lscope2:
	.section	.rodata.str1.1
.LC5:
	.string	"kernel panic at %s:%d: "
.LC6:
	.string	"\n"
	.text
	.align 16
	.stabs	"_panic:F(0,22)",36,0,0,_panic
	.stabs	"file:p(0,23)=*(0,2)",160,0,0,16
	.stabs	"line:p(0,1)",160,0,0,20
	.stabs	"fmt:p(0,23)",160,0,0,24
	.globl	_panic
	.type	_panic, @function
_panic:
	.stabn	68,0,63,.LM20-.LFBB3
.LM20:
.LFBB3:
.LFB2:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	subl	$4, %esp
	.cfi_def_cfa_offset 16
	.stabn	68,0,66,.LM21-.LFBB3
.LM21:
	movl	panicstr, %ebx
	.stabn	68,0,63,.LM22-.LFBB3
.LM22:
	movl	24(%esp), %esi
	.stabn	68,0,66,.LM23-.LFBB3
.LM23:
	testl	%ebx, %ebx
	je	.L13
	.align 16
.L11:
	.stabn	68,0,82,.LM24-.LFBB3
.LM24:
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	$0
	.cfi_def_cfa_offset 32
	call	monitor
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	jmp	.L11
.L13:
	.stabn	68,0,68,.LM25-.LFBB3
.LM25:
	movl	%esi, panicstr
	.stabn	68,0,71,.LM26-.LFBB3
.LM26:
/APP
/  71 "kern/init.c" 1
	cli; cld
/  0 "" 2
	.stabn	68,0,73,.LM27-.LFBB3
.LM27:
/NO_APP
	leal	28(%esp), %ebx
	.stabn	68,0,74,.LM28-.LFBB3
.LM28:
	pushl	%eax
	.cfi_def_cfa_offset 20
	pushl	24(%esp)
	.cfi_def_cfa_offset 24
	pushl	24(%esp)
	.cfi_def_cfa_offset 28
	pushl	$.LC5
	.cfi_def_cfa_offset 32
	call	cprintf
	.stabn	68,0,75,.LM29-.LFBB3
.LM29:
	popl	%edx
	.cfi_def_cfa_offset 28
	popl	%ecx
	.cfi_def_cfa_offset 24
	pushl	%ebx
	.cfi_def_cfa_offset 28
	pushl	%esi
	.cfi_def_cfa_offset 32
	call	vcprintf
	.stabn	68,0,76,.LM30-.LFBB3
.LM30:
	movl	$.LC6, (%esp)
	call	cprintf
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	jmp	.L11
	.cfi_endproc
.LFE2:
	.size	_panic, .-_panic
	.stabs	"fmt:r(0,23)",64,0,0,6
.Lscope3:
	.section	.rodata.str1.1
.LC7:
	.string	"kernel warning at %s:%d: "
	.text
	.align 16
	.stabs	"_warn:F(0,22)",36,0,0,_warn
	.stabs	"file:p(0,23)",160,0,0,16
	.stabs	"line:p(0,1)",160,0,0,20
	.stabs	"fmt:p(0,23)",160,0,0,24
	.globl	_warn
	.type	_warn, @function
_warn:
	.stabn	68,0,88,.LM31-.LFBB4
.LM31:
.LFBB4:
.LFB3:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	subl	$8, %esp
	.cfi_def_cfa_offset 16
	.stabn	68,0,91,.LM32-.LFBB4
.LM32:
	leal	28(%esp), %ebx
	.stabn	68,0,92,.LM33-.LFBB4
.LM33:
	subl	$4, %esp
	.cfi_def_cfa_offset 20
	pushl	24(%esp)
	.cfi_def_cfa_offset 24
	pushl	24(%esp)
	.cfi_def_cfa_offset 28
	pushl	$.LC7
	.cfi_def_cfa_offset 32
	call	cprintf
	.stabn	68,0,93,.LM34-.LFBB4
.LM34:
	popl	%eax
	.cfi_def_cfa_offset 28
	popl	%edx
	.cfi_def_cfa_offset 24
	pushl	%ebx
	.cfi_def_cfa_offset 28
	pushl	36(%esp)
	.cfi_def_cfa_offset 32
	call	vcprintf
	.stabn	68,0,94,.LM35-.LFBB4
.LM35:
	movl	$.LC6, (%esp)
	call	cprintf
	.stabn	68,0,96,.LM36-.LFBB4
.LM36:
	addl	$24, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE3:
	.size	_warn, .-_warn
.Lscope4:
	.comm	panicstr,4,4
	.stabs	"panicstr:G(0,23)",32,0,0,0
	.stabs	"",100,0,0,.Letext0
.Letext0:
	.ident	"GCC: (GNU) 9.2.0"
