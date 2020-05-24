	.file	"setjump.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Inside doJump(): nvar=%d rvar=%d vvar=%d\n"
	.align 8
.LC1:
	.string	"After longjmp(): nvar=%d rvar=%d vvar=%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB22:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$333, 12(%rsp)
	leaq	env(%rip), %rdi
	call	_setjmp@PLT
	testl	%eax, %eax
	je	.L6
	movl	12(%rsp), %ecx
	movl	$222, %edx
	movl	$111, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %edi
	call	exit@PLT
.L6:
	movl	$999, 12(%rsp)
	movl	12(%rsp), %ecx
	movl	$888, %edx
	movl	$777, %esi
	leaq	.LC0(%rip), %rdi
	call	printf@PLT
	movl	$1, %esi
	leaq	env(%rip), %rdi
	call	longjmp@PLT
	.cfi_endproc
.LFE22:
	.size	main, .-main
	.local	env
	.comm	env,200,32
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
