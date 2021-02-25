;Write X86/64 ALP to convert 4-digit Hex number into its equivalent BCD number and 5-digit BCD number into 
;its equivalent HEX number.Make your program user friendly to accept the choice from the user for
;(a)HEX to BCD
;(b)BCD to HEX 
;(c)EXIT 
;Display proper strings to prompt the user while accepting the 
;input and displaying the result (wherever necessary,use 64-bit registers ).

;Name : AKM
;Roll Number : 9999
;D.O.P   : 2019





%macro IO 4          ;Macro To Take Input or give Output
mov rax,%1           ;1st parameter to rax 
mov rdi,%2           ;2nd parameter to rdi
mov rsi,%3           ;3rd parameter to rsi
mov rdx,%4           ;4th parameter to rdx
syscall
%endmacro

section .data
		 	                                            
	menu db 10,"-----MENU------",10
	     db "1.HEX TO BCD",10         ;Menu     
	     db "2.BCD TO HEX",10
	     db "3.EXIT",10
	     db "Enter your choice:"
        
	lenm equ $-menu								    

	
	space db ' '                                                                
        endline db 10							             
	
	m1      db 10,"Enter 4-digit Hex number:"
	len1    equ $-m1
	m2      db 10,"Enter 5-digit BCD number:"
	len2 	equ $-m2
	m3	db 10,"Equivalent HEX is:"
	len3    equ $-m3
	m4 	db 10,"Equivalent BCD is:"
	len4    equ $-m4
	m5 	db 10,"!INVALID CODE",10
	len5    equ $-m5
              						     
	
	

section .bss
choice resb 2   ;choice variable
temp resb 16    ;reserving space	
hex resb 5	;reserving space for hex
bcd resb 6	;reseving space for bcd

section .code
global _start
_start:
	                      
	call _menu     	                             ;Call to print the menu
;--------------------------------------
_menu:                                               ;Menu

  _print:
        IO 1,1,menu,lenm                             ;Printing Menu
        IO 0,0,choice,2				     ;Getting choice	
       

	case1 : cmp byte[choice],'1'                 ;comparing choices
		jne case2	                     ;checking whether equal
		call hextobcd
		jmp  _print			     ;For looping purpose
       
	case2 : cmp byte[choice],'2'		     ;comparing choices	
		jne case3		             ;checking whether equal
		call bcdtohex
		jmp  _print                          ;For looping purpose
	
	case3 : cmp byte[choice],'3'                 ;comparing choices
		jne case4			     ;checking whether equal
		mov rax,60
		mov rdi,0
		syscall
						     ;For looping purpose
        case4 :
		IO 1,1,m5,len5                  ;Printing invalid choice
		jmp _print			     ;For looping purpose						
    


   ret
;----------------------------------------
display:
		mov rsi,temp
		mov rcx,4
	next:	rol bx,4
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
;-----------------------------------------

hextobcd:
		IO 1,1,m1,len1
		IO 0,0,hex,5
		call asciitohex
		
		
		mov ax,bx
   		mov bx,0AH
   		mov rcx,5
	
	label2: mov rdx,0
		div rbx
	        push dx
	        loop label2
	        
	        mov rcx,5
	        mov rsi,bcd
	        
	label3: pop dx
	        add dx,30H
	        mov [rsi],dx
	        inc rsi
	        loop label3
	        
	        IO 1,1,m4,len4
	        IO 1,1,bcd,5
		
  ret
;-----------------------------------------
 
bcdtohex:
 		IO 1,1,m2,len2
 		IO 0,0,bcd,6
 		IO 1,1,m3,len3	
 		mov rcx,5
 		mov rsi,bcd
 		mov rax,0
 		mov Rbx,10
 		
	label4:			
 		mul bx
 		mov dl,[rsi]
 		sub dl,30H
 		inc rsi
 		ADD rax,rdx
 		loop label4
 	
 	MOV BX,AX
 	call display
 		
 		
 				
 ret
 
;----------------------------------------- 

asciitohex:
	 	mov rbx,0
	 	mov rax,0
	        mov rcx,4
	        mov rsi,hex
	label1: rol bx,4
		
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
  
  

