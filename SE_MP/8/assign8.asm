;Problem : Program to find factorial of a number using recursion.
;Author : akm 
;DOP : 2019

%include "macro.asm"

section .data
	newline db 10
	msg2 db "Factorial is : ",10
	msg2len equ $-msg2

section .bss
	num resb 4
	tmp resb 16
	factorial resq 16
	
section .code
	global _start
	_start:
	mov rcx,0
	pop rcx
	cmp rcx,1
	je errorr
	pop rcx
	pop rcx
	mov rax,0
	mov rdx,0
up:
	mov al,byte[rcx+rdx]
	mov byte[num+rdx],al
	cmp byte[rcx+rdx],0
	je menu
	inc rdx
	jmp up


menu:		
	call ascii_hex
	mov [num],bl
	mov rcx,rbx
	mov rax,1
	mov qword[factorial],1
	call facto
	mov rbx,[factorial]
	display msg2,msg2len
	call disp64num

	mov rax,60			;mov sys_exit in rax
	mov rdi,1			;stdexit
	syscall	

facto: 
  	cmp rcx,0h
	je exit3
	push rcx
	cmp rcx,01
	jne ahead
	jmp exit2
   ahead:
	dec rcx
	call facto
  exit2:
	pop rax
	mul qword[factorial]
  exit3:
	mov qword[factorial],rax
	ret
 


ascii_hex:
		mov rax,0
		mov rcx,2
		mov rsi,num
		mov rbx,0
	   back2:	
		rol bx,4
		mov al,[rsi]
	   sub30H:
		sub al,30H
		add bx,ax
		inc rsi
		loop back2
		ret

disp64num:					;procedure for hex to ASCII 64 bit
		mov rcx,16			;mov 16 to rcx for loop to run 16 times
		mov rsi,tmp			;mov tmp to rsi
	next_digit2 :
		rol rbx,4			;rotate rbx left by 4
		mov rax,rbx			;mov rbx to rax
		and rax,0FH			;mask rax by 0FH
		cmp rax,9			;compare rax by 9
		jbe add30H2			;jump to add30H if rax < 9
		add rax,7H			;add 7H to rax
	add30H2:
		add rax,30H			;add 30H to al
		mov[rsi],rax			;mov rax to rsi value (that is tmp)
		inc rsi				;increment rsi by 1
		loop next_digit2		;loop
		display tmp,16			;display tmp
		display newline,1		;add new line
		ret

errorr:
	mov rax,60			;mov sys_exit in rax
	mov rdi,1			;stdexit
	syscall	
