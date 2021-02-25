;Write 64 bit ALP to count Positive and Negative numbers from given array
;Name : AKM
;Roll Number : 9999
;Date : 2019

%macro IO 4			;Macro To Take Input or give Output
	mov rax , %1		;1st parameter to rax
	mov rdi , %2		;2nd parameter to rdi
	mov rsi , %3		;3rd parameter to rsi
	mov rdx , %4		;4th parameter to rdx
	syscall
%endmacro

section .data
	num dq 013FH,0FBA01233367819AAH,1234H,0B234567891234156H,1H,151H,0000000000000000H, ;Array Initialization
	msg1 db "Positive Count is : "		;Msg 1
	msg1len equ $-msg1			;Length of Msg 1
	msg2 db "Negative Count is : "		;Msg 2
	msg2len equ $-msg2			;Length of Msg 2
	newline db 10				;Newline
	
	pos db "Value at Position "
	poslen equ $-pos

section .bss
	pcount resb 1				;Count of Positive Number 
	ncount resb 1				;Count of Negative Number
	temp resb 2				;Temporary variable
	temp2 resb 16				;Temp2 Variable

section .text
	global _start
_start:
	
	IO 1,1,newline,1			;Newline
	mov rcx , 7				;rcx = 7
	mov rsi , num				;rsi points to address of first element of array num
nextnum:
	mov rax,[rsi]				;rax gets value of address stored in rsi
	push rax				;Push rax
	push rsi				;Push rsi
	push rcx				;Push rcx
	mov rbx,rax				
	call dispnum				;Print Array Element
	IO 1,1,newline,1			;Newline
	pop rcx					;Pop rcx from stack
	pop rsi					;Pop rsi from stack
	pop rax					;Pop rax from stack
						
	bt rax , 63				;check 63rd Bit of rax
	jc next					;Jump Carry Checks if carry gen is 1 or not
	inc byte[pcount]			;increase count of pcount by 1 byte
	jmp skip
next:
	inc byte[ncount]			;increase count of ncount by 1 byte
skip:
	add rsi , 8				;to point rsi to next address , we add 8 bits to it 
	loop nextnum				;Loop goto nextnum


	
mov rax , 60
	mov rdi , 1				;End
	syscall

disp8num:
	mov rsi , temp
	mov rcx , 2
nextnum1:
	rol bl , 4				;rotate bl register by 4 byte
	mov al , bl				;copy bl to al register
	and al , 0FH				;get last bit
	cmp al,9				;compare al with 9
	jbe add30h				;if al <= 9 jump to add30h
	add al,7H				;else add 7H to al
add30h:
	add al,30H				;add 30H to al
	mov [rsi],al				;value at address pointed by rsi is changed to al
	inc rsi					;rsi is increased
	loop nextnum1				;loop nextnum1
	IO 1,1,temp,2				;Display temp
ret

dispnum:
	mov rsi , temp2
	mov rcx , 16
nextnum2:
	rol rbx , 4				;rotate bl register by 4 byte
	mov al , bl				;copy bl to al register
	and al , 0FH				;get last bit
	cmp al,9				;compare al with 9
	jbe add30HH				;if al <= 9 jump to add30h
	add al,7H				;else add 7H to al
add30HH:
	add al,30H				;add 30H to al
	mov [rsi],al				;value at address pointed by rsi is changed to al
	inc rsi					;rsi is increased
	loop nextnum2				;loop nextnum1
	IO 1,1,temp2,16				;Display temp
ret


