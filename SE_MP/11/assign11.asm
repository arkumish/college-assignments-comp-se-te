;Problem Statement : Write a Program to obtain Mean, Variance and Standard Deviation of given Data.
;Author : akm
%include"macro.asm"

section .data 
	msg db "Enter Number of Elements : ",10,0

	msg1 db "Mean : ",0

	msg2 db "Variance : ",0

	msg3 db "Standard Deviation : ",0

	two dq 2
	fmt db "%lf",0	
	infmt db "%lf",10,0
	fmt2 db "%ld",10,0
        three dq 5

section .bss
mean resq 1
arr resq 10
n resq 1
n2 resq 1
x resq 1
var resq 1
sd resq 1

section .code
global main
extern printf
extern scanf

main:
push rbp
mov rbp, rsp


        mov rdi, msg
	mov rax,0
	call printf

        ;mov rdi,fmt2
        ;mov rsi,n
        ;movq xmm0,rsi
        ;mov rax,1
        ;call scanf
        
        mov rsi,arr
        mov rcx,[three]  
back3:	
	push rcx
	push rsi
	mov rdi,fmt
	movq xmm0,rsi
	mov rax,0
	call scanf
	pop rsi
	pop rcx
	add rsi,8
	loop back3
	

	finit
        fild qword[three]
        fstp qword[n]
	fldz
	mov rsi,arr
	mov rcx,[three]
back:
        fadd qword[rsi]
	add rsi,8
	loop back
	
	fdiv qword[n]
	fstp qword[mean]
	
	mov rdi, msg1
	mov rax,0
	call printf
	
	mov rdi,infmt
        movq xmm0,[mean]
        mov rax,1
        call printf
        
        fldz    
	mov rsi,arr
	mov rcx,[three]
back2:
        fld qword[rsi]
        fsub qword[mean]
        fstp qword[x]
        fld qword[x]
        fmul qword[x]
        fstp qword[x]
        fadd qword[x]
        
	add rsi,8       
	loop back2
	
	fdiv qword[n]
	fstp qword[var]
	
	mov rdi, msg2
	mov rax,0
	call printf
	
	mov rdi,infmt
        movq xmm0,[var]
        mov rax,1
        call printf
        
        fld qword[var]
        fsqrt
        fstp qword[sd]
        
        mov rdi, msg3
	mov rax,0
	call printf
        
        mov rdi,infmt
        movq xmm0,[sd]
        mov rax,1
        call printf
        

mov rsp, rbp
pop rbp
 
mov rax,60			;mov sys_exit in rax
mov rdi,1			;stdexit
syscall	
