;Problem Statement : Write a Program to find Roots of a Quadratic Equation.
;Author : akm



%include"macro.asm"


section .data
inpmsg db "Enter Coffecient a,b and c",10,0
	inpmsglen equ $-inpmsg
	two 	dq 2
	m0 db "Delta is:%lf",10,0
        m1 db "Roots are Real",10,0
	m2 db "Roots are Imaginary",10,0
	m3 db "r1=%lf  r2=%lf",10,0
	m4 db "r1 = %lf + %lf i",10,0
	m5 db "r2 = %lf - %lf i",10,0
	fmt db "%lf",0
	infmt db 10,"a = %lf",10,"b = %lf",10,"c = %lf",10,0
        four dq 4

section .bss
a resq 1
b resq 1
c resq 1
bb resq 1
delta resq 1
fac resq 1
ta resq 1
rdelta resq 1
r1 resq 1
r2 resq 1
s1 resq 1
s2 resq 1




section .code
global main
extern printf
extern scanf

main:

push rbp
mov rbp, rsp


	mov rdi, inpmsg
	mov rax,0
	call printf
	
	mov rdi,fmt		;scan a
	mov rsi,a
	call scanf

	
	mov rdi,fmt		;scan b
	mov rsi,b
	call scanf
	
	mov rdi,fmt		;scan c
	mov rsi,c
	call scanf
			 
	mov rdi,infmt
	movq xmm0,[a]
	movq xmm1,[b]
	movq xmm2,[c]
	mov rax,3
	call printf

   finit
   fld qword[b]
   fmul qword[b]
   fstp qword[bb]
   
   fild qword[four]
   fmul qword[a]
   fmul qword[c]
   fstp qword[fac]
   
   fld qword[bb]
   fsub qword[fac]
   ;fld qword[delta]
   ;fsqrt
   ;fstp qword[rdelta]
   fstp qword[delta]

   fild qword[two]
   fmul qword[a]
   fstp qword[ta]

   
   fld qword[delta]
   ftst
   fstsw ax
   sahf
   jb imaginary
   
   real:
    mov rdi,m1
    mov rax,0
    call printf


	
    fld qword[delta]
    fsqrt
    fstp qword[rdelta]

	
	fldz
	fsub qword[b]
	fadd qword[rdelta]
	fdiv qword[ta]
	fstp qword[r1]

	fldz
	fsub qword[b]
	fsub qword[rdelta]
	fdiv qword[ta]
	fstp qword[r2]

	mov rdi,m3
	movq xmm0,[r1]
	movq xmm1,[r2]
	mov rax,2
	call printf
	
	jmp skip




   imaginary:
   mov rdi,m2
   mov rax,0
   call printf
   fldz
   fsub qword[delta]
   fsqrt
   fstp qword[rdelta]
   

   fldz
   fsub qword[b]
   fdiv qword[ta]
   fstp qword[s1]
   
   fld qword[rdelta]
   fdiv qword[ta]
   fstp qword[s2]

   mov rdi,m4
   movq xmm0,[s1]
   movq xmm1,[s2]
   mov rax,2
   call printf
   
   mov rdi,m5
   movq xmm0,[s1]
   movq xmm1,[s2]
   mov rax,2
   call printf
   

skip:

mov rsp, rbp
pop rbp
 
mov rax,60			;mov sys_exit in rax
mov rdi,1			;stdexit
syscall	
