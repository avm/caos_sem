	.file	"main.c"
	.text
	.globl	__asan_stack_malloc_2
	.section	.rodata
.LC0:
	.string	"1 32 88 10 statbuf:10"
	.align 32
.LC1:
	.string	"%lld\n"
	.zero	58
	.text
	.globl	main
	.type	main, @function
main:
.LASANPC6:
.LFB6:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x70,0x6
	.cfi_escape 0x10,0x7,0x2,0x75,0x7c
	.cfi_escape 0x10,0x6,0x2,0x75,0x78
	.cfi_escape 0x10,0x3,0x2,0x75,0x74
	subl	$200, %esp
	movl	%ecx, -204(%ebp)
	leal	-184(%ebp), %esi
	movl	%esi, -216(%ebp)
	cmpl	$0, __asan_option_detect_stack_use_after_return
	je	.L1
	subl	$12, %esp
	pushl	$160
	call	__asan_stack_malloc_2
	addl	$16, %esp
	testl	%eax, %eax
	je	.L1
	movl	%eax, %esi
.L1:
	leal	160(%esi), %eax
	movl	%eax, %edi
	movl	$1102416563, (%esi)
	movl	$.LC0, 4(%esi)
	movl	$.LASANPC6, 8(%esi)
	movl	%esi, %ebx
	shrl	$3, %ebx
	movl	$-235802127, 536870912(%ebx)
	movl	$-218103808, 536870924(%ebx)
	movl	$-202116109, 536870928(%ebx)
	movl	$0, -192(%ebp)
	movl	$0, -188(%ebp)
	movl	$1, -200(%ebp)
	jmp	.L5
.L11:
	movl	-200(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	-204(%ebp), %eax
	movl	4(%eax), %eax
	addl	%edx, %eax
	movl	%eax, -208(%ebp)
	movl	%eax, %ecx
	movl	%ecx, %eax
	shrl	$3, %eax
	addl	$536870912, %eax
	movzbl	(%eax), %edx
	testb	%dl, %dl
	setne	-209(%ebp)
	movl	%ecx, %eax
	andl	$7, %eax
	addl	$3, %eax
	cmpb	%dl, %al
	setge	%al
	andb	-209(%ebp), %al
	testb	%al, %al
	je	.L6
	subl	$12, %esp
	pushl	%ecx
	call	__asan_report_load4
.L6:
	movl	-208(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -196(%ebp)
	leal	-128(%edi), %eax
	shrl	$3, %eax
	addl	$536870912, %eax
	movl	$0, (%eax)
	movl	$0, 4(%eax)
	movw	$0, 8(%eax)
	movb	$0, 10(%eax)
	subl	$8, %esp
	leal	-128(%edi), %eax
	pushl	%eax
	pushl	-196(%ebp)
	call	lstat
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L7
	leal	-128(%edi), %eax
	addl	$20, %eax
	movl	%eax, %ecx
	movl	%ecx, %eax
	shrl	$3, %eax
	addl	$536870912, %eax
	movzbl	(%eax), %edx
	testb	%dl, %dl
	setne	-208(%ebp)
	movl	%ecx, %eax
	andl	$7, %eax
	addl	$3, %eax
	cmpb	%dl, %al
	setge	%al
	andb	-208(%ebp), %al
	testb	%al, %al
	je	.L8
	subl	$12, %esp
	pushl	%ecx
	call	__asan_report_load4
.L8:
	movl	-108(%edi), %eax
	cmpl	$1, %eax
	jne	.L7
	leal	-128(%edi), %eax
	addl	$16, %eax
	movl	%eax, %ecx
	movl	%ecx, %eax
	shrl	$3, %eax
	addl	$536870912, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	setne	%dl
	cmpb	$3, %al
	setle	%al
	andl	%edx, %eax
	testb	%al, %al
	je	.L9
	subl	$12, %esp
	pushl	%ecx
	call	__asan_report_load4
.L9:
	movl	-112(%edi), %eax
	andl	$61440, %eax
	cmpl	$32768, %eax
	jne	.L7
	leal	-128(%edi), %eax
	addl	$44, %eax
	movl	%eax, %ecx
	movl	%ecx, %eax
	shrl	$3, %eax
	addl	$536870912, %eax
	movzbl	(%eax), %edx
	testb	%dl, %dl
	setne	-208(%ebp)
	movl	%ecx, %eax
	andl	$7, %eax
	addl	$3, %eax
	cmpb	%dl, %al
	setge	%al
	andb	-208(%ebp), %al
	testb	%al, %al
	je	.L10
	subl	$12, %esp
	pushl	%ecx
	call	__asan_report_load4
.L10:
	movl	-84(%edi), %eax
	cltd
	addl	%eax, -192(%ebp)
	adcl	%edx, -188(%ebp)
.L7:
	leal	-128(%edi), %eax
	shrl	$3, %eax
	addl	$536870912, %eax
	movl	$-117901064, (%eax)
	movl	$-117901064, 4(%eax)
	movw	$-1800, 8(%eax)
	movb	$-8, 10(%eax)
	addl	$1, -200(%ebp)
.L5:
	movl	-200(%ebp), %eax
	movl	-204(%ebp), %ecx
	cmpl	(%ecx), %eax
	jl	.L11
	subl	$4, %esp
	pushl	-188(%ebp)
	pushl	-192(%ebp)
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	cmpl	%esi, -216(%ebp)
	je	.L2
	movl	$1172321806, (%esi)
	movl	$-168430091, 536870912(%ebx)
	movl	$-168430091, 536870916(%ebx)
	movl	$-168430091, 536870920(%ebx)
	movl	$-168430091, 536870924(%ebx)
	movl	$-168430091, 536870928(%ebx)
	jmp	.L3
.L2:
	movl	$0, 536870912(%ebx)
	movl	$0, 536870916(%ebx)
	movl	$0, 536870920(%ebx)
	movl	$0, 536870924(%ebx)
	movl	$0, 536870928(%ebx)
.L3:
	leal	-16(%ebp), %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.section	.rodata
.LC2:
	.string	"*.LC1"
.LC3:
	.string	"main.c"
	.data
	.align 32
	.type	.LASAN0, @object
	.size	.LASAN0, 32
.LASAN0:
	.long	.LC1
	.long	6
	.long	64
	.long	.LC2
	.long	.LC3
	.long	0
	.long	0
	.long	0
	.text
	.type	_GLOBAL__sub_D_00099_0_main, @function
_GLOBAL__sub_D_00099_0_main:
.LFB7:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$8, %esp
	pushl	$1
	pushl	$.LASAN0
	call	__asan_unregister_globals
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE7:
	.size	_GLOBAL__sub_D_00099_0_main, .-_GLOBAL__sub_D_00099_0_main
	.section	.fini_array.00099,"aw"
	.align 4
	.long	_GLOBAL__sub_D_00099_0_main
	.text
	.type	_GLOBAL__sub_I_00099_1_main, @function
_GLOBAL__sub_I_00099_1_main:
.LFB8:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	call	__asan_init
	call	__asan_version_mismatch_check_v8
	subl	$8, %esp
	pushl	$1
	pushl	$.LASAN0
	call	__asan_register_globals
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE8:
	.size	_GLOBAL__sub_I_00099_1_main, .-_GLOBAL__sub_I_00099_1_main
	.section	.init_array.00099,"aw"
	.align 4
	.long	_GLOBAL__sub_I_00099_1_main
	.ident	"GCC: (GNU) 9.3.1 20200408 (Red Hat 9.3.1-2)"
	.section	.note.GNU-stack,"",@progbits
