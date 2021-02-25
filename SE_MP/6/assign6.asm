;Problem : Program to take input from file, bubble sort and write back to the same file.
;Author : akm 


%include "macro.asm"
section .data
	msg db "Enter the name of the file",9
	msglen equ $-msg
	msg1 db "Sorted Array : ",9
	msg1len equ $-msg1
	err db "File cannot be open",10
	errlen equ $-err
	newline db 10
	
section .bss
	fname resb 10
	flen resq 1
	fhandler resb 8
	readbuf resb 1024
	tmp resb 16
	num resq 10
	cnt resb 2
	writebuff resb 1024
   	bufflen resq 1
	writebackbuf resb 1024
	writebackbuflen resq 1

section .text
	global _start
	_start:
	display msg,msglen
	read fname,10
	dec rax
	mov byte[fname+rax],0
	
	 
	fopen fname
	cmp rax,-2
	je errorr
	mov [fhandler],rax
	frw 0,[fhandler],readbuf,1024
	mov [flen],rax

	mov byte[cnt],0
	mov rdi,num
	mov rbx,0
	mov rcx,[flen]
	mov rsi,readbuf
loop1:
        	rol rbx,4
	mov al,byte[rsi]
	sub al,30H
	add rbx,rax
	inc rsi
	cmp byte[rsi],','
	jne back
	mov [rdi],rbx
	inc byte[cnt]
	mov rbx,0
	inc rsi
	add rdi,8
back:
	loop loop1
	


	call bubble




	mov rsi, num
	 mov rdi, writebackbuf
	 mov rcx, qword[cnt]
	 loop_main:
	 	push rcx
	 	mov rax, qword[rsi]
	 	
	 	mov rbx, 16
	 	mov rcx, 0	
	 	loop_1:
	 		mov rdx, 0
	 		div rbx
	 		inc rcx
	 		push dx
	 	cmp rax, 0
	 	jne loop_1
	 	
	 	loop_2:
	 		pop dx
	 		add dx, 30h
	 		mov [rdi], dl
	 		inc qword[writebackbuflen]
	 		inc rdi
	 	loop loop_2
	 	mov dl, ','
	 	mov [rdi], dl
	 	inc qword[writebackbuflen]
	 	inc rdi
	 	
	 	pop rcx
	 	add rsi, 8
	 loop loop_main


      	frw 1,[fhandler],newline,1
   	frw 1, [fhandler], writebackbuf, [writebackbuflen]


	mov rax,60
	mov rdi,1		
	syscall	

	errorr:
	display err,errlen
	mov rax,60
	mov rdi,1		
	syscall	

	


bubble:
	mov rbp,[cnt]
	dec rbp
	mov rcx,0	

oloop:  mov rbx,0
	mov rsi,num

iloop:	mov rdi,rsi
	add rdi,8
	mov rax,[rsi]
	cmp rax,[rdi]
	jbe next3

	mov rdx,[rdi]
	mov [rdi],rax
	mov [rsi],rdx

next3: 	add rsi,8
	inc rbx
	cmp rbx,rbp
	jb iloop

	inc rcx
	cmp rcx,rbp
	jb oloop
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
