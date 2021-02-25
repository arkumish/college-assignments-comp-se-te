;Problem : Program to implement DOS Commands : TYPE, COPY and DELETE.
;Author : akm 


%include "macro.asm"

section .data
	newline db 10
	menumsg db "Enter Your Choice : ",10
		db "1. TYPE",10
		db "2. COPY",10
		db "3. DELETE",10
		db "4. EXIT",10
	menulen equ $-menumsg
	msg1 db "ERROR",10
	msg1len equ $-msg1

section .bss
	choice resb 2
	fname resb 10
	fname2 resb 10
	flen resq 1
	fhandler resb 8
	readbuf resb 1024
	tmp resb 16
	
section .text
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
	mov byte[fname+rdx],al
	cmp byte[rcx+rdx],0
	je menu
	inc rdx
	jmp up

menu:	
	display menumsg,menulen
		read choice,2
	case1: 	cmp byte[choice],'1'		
	       	jne case2			
		call type	
		jmp menu			
	case2: 	cmp byte[choice],'2'
	       	jne case3	
		call copy
		jmp menu
	case3: 	cmp byte[choice],'3'
	       	jne case4	
		call delete
		jmp menu
	case4:	mov rax,60			;mov sys_exit in rax
		mov rdi,1			;stdexit
		syscall	

type:
	fopen fname
	cmp rax,-2	
	je errorr
	mov [fhandler],rax
	read readbuf,1024
	mov [flen],rax
	frw 1,[fhandler],readbuf,[flen]
	fclose fname
	ret

copy:
	fopen fname
	cmp rax,-2	
	je errorr
	mov [fhandler],rax
	frw 0,[fhandler],readbuf,1024
	mov [flen],rax
	fclose fname

	mov rax,0
	read fname2,10
	dec rax
	mov byte[fname2+rax],0
	fopen fname2
	cmp rax,-2	
	je errorr
	mov [fhandler],rax
	frw 1, [fhandler], readbuf, [flen]
	fclose fname2
	ret

delete:
	fdelete fname2
	ret

errorr:
	display msg1,msg1len
	mov rax,60			;mov sys_exit in rax
	mov rdi,1			;stdexit
	syscall	
