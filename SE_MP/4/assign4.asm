;Program to multiply two 8 bit numbers 
;Name : AKM
;Roll Number : 9999
;D.O.P :2019

%macro IO 4          ;Macro To Take Input or give Output
mov rax,%1           ;1st parameter to rax 
mov rdi,%2           ;2nd parameter to rdi
mov rsi,%3           ;3rd parameter to rsi
mov rdx,%4           ;4th parameter to rdx
syscall
%endmacro

section .data

m1 db 10,"----------MENU--------------",10
   db "1.Multiplication by successive addition ",10
   db "2.Multiplication by add and shift method ",10
   db "3.Exit",10
   db "Enter your choice:"

len1 equ $-m1
m2 db "Enter first number:"
len2 equ $-m2
m3 db "Enter second number:"
len3 equ $-m3
invalid db 10,"INVALID",10
m4 equ $-invalid
endline db 10
m5 db 10,"Product:"
len5 equ $-m5 

section .bss
num1 resb 2
num2 resb 2
num resb 3
temp resb 2
choice resb 2


section .code
global _start
_start:

IO 1,1,problem,msg
call _menu


mov rax,60
mov rdi,0
syscall
;---------------------------------------

_menu:

   _print:		
		IO 1,1,m1,len1
        	IO 0,0,choice,2

case1: cmp byte[choice],'1'
	jne case2
	call product
	jmp _print

case2: cmp byte[choice],'2'
	jne case3
	call addandshift
	jmp _print
	
case3: cmp byte[choice],'3'
	jne case4
	mov rax,60
	mov rdi,0
	syscall

case4: IO 1,1,invalid,m4
	jmp _print
        
;---------------------------------------
input:
	IO 1,1,m2,len2
	IO 0,0,num,3
	call asciitohex
	mov [num1],bx;
    
    IO 1,1,m3,len3
	IO 0,0,num,3
	call asciitohex
	mov [num2],bx;

ret

;---------------------------------------
product:
		call input
		
		
		mov al,0
                mov cl,[num2]   
                
          label:add ax,[num1]
                loop label
            
                mov bx,ax
                call display
   ret
	

addandshift:
      call input
      mov al,[num1]
      mov bl,[num2]
      mov dx,0
      mov cl,8

   labela: shr bl,1
           jnc nex
           
           add dx,ax
           
           nex: 
           		shl ax,1
           
           loop labela

      mov bx,dx
      call display

    ret


display:
		mov rsi,temp
		mov rcx,4
		
	next:rol bx,4
		 mov AL,BL
		 and AL,0FH
		 cmp AL,09H
		 jbe add_30
		 add AL,07H
	add_30:
		add AL,30H
		mov [rsi],AL
		inc rsi
		loop next
		IO 1,1,temp,4
  ret
	

asciitohex:
	 	mov rbx,0
	 	mov rax,0
	 	mov rsi,num
	    mov rcx,2
	label1: 
	    rol bx,4	
		mov al,[rsi]
		cmp al,'9'
		jbe sub_30h
		sub al,7H
	sub_30h:
		sub al,30H
		add bX,aX
		inc rsi
		loop label1	
		
   ret        
;-----------------------------------------

