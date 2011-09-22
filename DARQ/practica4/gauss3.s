	.file	"gauss.c"
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 4
.LC0:
	.string	"Uso:%s <tama\361o-matriz> <numero-de-iteraciones> <numero-de-pruebas>\n"
	.align 4
.LC1:
	.string	"ERROR: el tama\361o de la matriz (%d) debe ser menor que MAXSIZE (%d)\n"
	.align 4
.LC2:
	.string	"ERROR: el n\372mero de iteraciones y el de pruebas debe ser mayor que 0\n"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC5:
	.string	"\n******** Datos ********"
	.section	.rodata.str1.4
	.align 4
.LC6:
	.string	"Resolucion del temporizador: %7.1f usg (%d intervalos/seg)\n"
	.align 4
.LC7:
	.string	"Tama\361o_matriz, limit, repeat:  %dx%d, %d, %d\n"
	.section	.rodata.str1.1
.LC8:
	.string	"Ejecutando gauss v1.3.\n"
	.section	.rodata.str1.4
	.align 4
.LC10:
	.string	"*** Test %02d = %8.3f usg (%8.3f)\n"
	.align 4
.LC11:
	.string	"AVISO: tiempo de ejecuci\363n menor que la resoluci\363n del reloj"
	.align 4
.LC13:
	.string	"AVISO: tiempo de ejecuci\363n (%4.2f usg) menor que 20 ticks del reloj (%4.2f usg)\n"
	.align 4
.LC15:
	.string	"AVISO: Varianza de las mediciones demasiado alta"
	.section	.rodata.str1.1
.LC16:
	.string	"\n******** Resultados ********"
	.section	.rodata.str1.4
	.align 4
.LC17:
	.string	"Tiempo medio de ejecuci\363n de L/U    = %8.3f usg\n"
	.align 4
.LC18:
	.string	"Tiempo medio de ejecuci\363n de limit  = %8.0f usg\n"
	.align 4
.LC19:
	.string	"Tiempo total de ejecuci\363n de repeat = %8.0f usg\n\n"
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC3:
	.long	1082130432
	.align 4
.LC4:
	.long	1232348160
	.align 4
.LC12:
	.long	1101004800
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC14:
	.long	1202590843
	.long	1063549665
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	subl	$136, %esp
	movl	4(%ecx), %ebx
	cmpl	$3, (%ecx)
	jle	.L43
	movl	$0, 12(%esp)
	movl	$10, 8(%esp)
	movl	$0, 4(%esp)
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	__strtol_internal
	cmpl	$4104, %eax
	movl	%eax, %esi
	jg	.L44
	movl	$0, 12(%esp)
	movl	$10, 8(%esp)
	movl	$0, 4(%esp)
	movl	8(%ebx), %eax
	movl	%eax, (%esp)
	call	__strtol_internal
	movl	$0, 12(%esp)
	movl	$10, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, %edi
	movl	12(%ebx), %eax
	movl	%eax, (%esp)
	call	__strtol_internal
	testl	%edi, %edi
	movl	%eax, -56(%ebp)
	jle	.L6
	testl	%eax, %eax
	jle	.L6
	testl	%esi, %esi
	.p2align 4,,3
	jle	.L9
	xorl	%ecx, %ecx
	flds	.LC3
	xorl	%ebx, %ebx
.L10:
	pushl	%ecx
	xorl	%edx, %edx
	fildl	(%esp)
	leal	A(%ebx), %eax
	addl	$4, %esp
	fld	%st(0)
	fadd	%st(2), %st
	fstpl	B(,%ecx,8)
	fld	%st(0)
	fadd	%st(1), %st
	fstpl	P(,%ecx,8)
.L11:
	pushl	%edx
	addl	$1, %edx
	fildl	(%esp)
	addl	$4, %esp
	fadd	%st(1), %st
	fstpl	(%eax)
	addl	$8, %eax
	cmpl	%esi, %edx
	jne	.L11
	fstp	%st(0)
	addl	$1, %ecx
	addl	$32832, %ebx
	cmpl	%esi, %ecx
	jne	.L10
	fstp	%st(0)
.L9:
	movl	$2, (%esp)
	call	sysconf
	pushl	%eax
	movl	%eax, %ebx
	fildl	(%esp)
	addl	$4, %esp
	flds	.LC4
	fdivp	%st, %st(1)
	movl	$.LC5, (%esp)
	fstps	-64(%ebp)
	call	puts
	movl	%ebx, 12(%esp)
	movl	$.LC6, (%esp)
	flds	-64(%ebp)
	fstl	-96(%ebp)
	fstpl	4(%esp)
	call	printf
	movl	-56(%ebp), %eax
	movl	%edi, 12(%esp)
	movl	%esi, 8(%esp)
	movl	%esi, 4(%esp)
	movl	%eax, 16(%esp)
	movl	$.LC7, (%esp)
	call	printf
	movl	$.LC8, (%esp)
	call	puts
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	times
	movl	-40(%ebp), %eax
	movl	%eax, -72(%ebp)
	movl	-56(%ebp), %eax
	testl	%eax, %eax
	jle	.L45
	pushl	%edi
	fildl	(%esp)
	addl	$4, %esp
	movl	$0, -88(%ebp)
	fstps	-100(%ebp)
	movl	$0, -80(%ebp)
	movl	$0, -76(%ebp)
.L16:
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	times
	testl	%edi, %edi
	movl	%eax, -68(%ebp)
	movl	-40(%ebp), %eax
	movl	%eax, -84(%ebp)
	jle	.L17
	xorl	%ebx, %ebx
.L19:
	xorl	%ecx, %ecx
	testl	%esi, %esi
	movl	$0, A
	movl	$0, A+4
	jle	.L20
.L22:
	imull	$32832, %ecx, %eax
	fldl	P(,%ecx,8)
	xorl	%edx, %edx
	addl	$A, %eax
	.p2align 4,,7
.L23:
	fldl	B(,%edx,8)
	addl	$1, %edx
	fmul	%st(1), %st
	fsubrl	(%eax)
	fstpl	(%eax)
	addl	$8, %eax
	cmpl	%esi, %edx
	jne	.L23
	fstp	%st(0)
	addl	$1, %ecx
	cmpl	%edx, %ecx
	jne	.L22
.L20:
	addl	$1, %ebx
	cmpl	%edi, %ebx
	jne	.L19
.L17:
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	times
	movl	-40(%ebp), %ebx
	subl	-84(%ebp), %ebx
	addl	$1, -88(%ebp)
	subl	-68(%ebp), %eax
	pushl	%ebx
	flds	-100(%ebp)
	fstps	-48(%ebp)
	fildl	(%esp)
	fmuls	-64(%ebp)
	movl	%eax, (%esp)
	movl	-88(%ebp), %eax
	fildl	(%esp)
	addl	$4, %esp
	fmuls	-64(%ebp)
	movl	%eax, 4(%esp)
	movl	$.LC10, (%esp)
	fdivs	-48(%ebp)
	fstpl	16(%esp)
	flds	-48(%ebp)
	fdivr	%st(1), %st
	fstpl	8(%esp)
	fstps	-120(%ebp)
	call	printf
	testl	%ebx, %ebx
	flds	-120(%ebp)
	je	.L46
	cmpl	$19, %ebx
	jg	.L48
	fldl	-96(%ebp)
	fmuls	.LC12
	movl	$.LC13, (%esp)
	fstpl	12(%esp)
	fstpl	4(%esp)
	call	printf
	jmp	.L27
.L48:
	fstp	%st(0)
.L27:
	movl	%ebx, %eax
	imull	%ebx, %eax
	addl	%eax, -76(%ebp)
	movl	-56(%ebp), %eax
	addl	%ebx, -80(%ebp)
	cmpl	%eax, -88(%ebp)
	jne	.L16
	fildl	-80(%ebp)
	fstps	-52(%ebp)
	fildl	-76(%ebp)
.L15:
	leal	-40(%ebp), %eax
	fstps	-120(%ebp)
	movl	%eax, (%esp)
	call	times
	movl	-40(%ebp), %ebx
	fildl	-56(%ebp)
	flds	-52(%ebp)
	fdiv	%st(1), %st
	fsts	-60(%ebp)
	fmul	%st(0), %st
	flds	-120(%ebp)
	fdivp	%st, %st(2)
	fsubr	%st, %st(1)
	fdivrp	%st, %st(1)
	fldl	.LC14
	fxch	%st(1)
	fucompp
	fnstsw	%ax
	sahf
	ja	.L47
.L30:
	movl	$.LC16, (%esp)
	call	puts
	movl	$.LC17, (%esp)
	flds	-60(%ebp)
	fdivs	-48(%ebp)
	fmuls	-64(%ebp)
	fstpl	4(%esp)
	call	printf
	movl	$.LC18, (%esp)
	flds	-60(%ebp)
	fmuls	-64(%ebp)
	fstpl	4(%esp)
	call	printf
	subl	-72(%ebp), %ebx
	pushl	%ebx
	fildl	(%esp)
	addl	$4, %esp
	fmuls	-64(%ebp)
	movl	$.LC19, (%esp)
	fstpl	4(%esp)
	call	printf
	movl	$0, (%esp)
	call	exit
.L46:
	fstp	%st(0)
	movl	$.LC11, (%esp)
	call	puts
	jmp	.L27
.L6:
	movl	stderr, %eax
	movl	$69, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC2, (%esp)
	movl	%eax, 12(%esp)
	call	fwrite
	movl	$1, (%esp)
	call	exit
.L43:
	movl	(%ebx), %eax
	movl	$.LC0, (%esp)
	movl	%eax, 4(%esp)
	call	printf
	movl	$-1, (%esp)
	call	exit
.L47:
	movl	$.LC15, (%esp)
	call	puts
	jmp	.L30
.L45:
	pushl	%edi
	fildl	(%esp)
	addl	$4, %esp
	fstps	-48(%ebp)
	fldz
	fsts	-52(%ebp)
	jmp	.L15
.L44:
	movl	%eax, 8(%esp)
	movl	stderr, %eax
	movl	$4104, 12(%esp)
	movl	$.LC1, 4(%esp)
	movl	%eax, (%esp)
	call	fprintf
	movl	$1, (%esp)
	call	exit
	.size	main, .-main
	.comm	A,134742528,32
	.comm	P,32832,32
	.comm	B,32832,32
	.ident	"GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-46)"
	.section	.note.GNU-stack,"",@progbits
