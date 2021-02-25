;Write X86/64 ALP to perform non-overlapped and overlapped block transfer (with and without string specific instructions).
;Author:AKM
;D.O.P : 2019
  


%macro IO 4          ;Macro To Take Input or give Output
mov rax,%1           ;1st parameter to rax 
mov rdi,%2           ;2nd parameter to rdi
mov rsi,%3           ;3rd parameter to rsi
mov rdx,%4           ;4th parameter to rdx
syscall
%endmacro

section .data
	
	menu db "1.Non Overlapped Block Transfer without string specific",10         ;Menu     
	     db "2.Non Overlapped Block Transfer with string specific",10
	     db "3.Overlapped Block Transfer without string specific",10
	     db "4.Overlapped Block Transfer with string specific",10
             db "5.Exit",10
	     db "Enter your choice:"
        
	len1 equ $-menu								     ;Length of Menu

	source db "Block before transfer",10						     ;Source Array Name
        len3 equ $-source                                                            ;Length of source array
    
        destination db "Block After transfer",10				             ;Destination Array Name
        len4 equ $-destination							     ;Length of Destination Array	

	space db ' '                                                                 ;Space
        endline db 10							             ;Endline character
	
        invalid db "!Invalid Choice",10 					     ;Option to show invalid
	len2 equ $invalid							     ;Length of invalid string
	
	src dq 12, 13, 14, 10, 15                                                    ;Array Initialization
	dest dq 00, 00, 00, 00, 00                                                   ;Array Initialization
 newline db 10				;Newline

section .bss
choice resb 2  ;choice variable
temp resb 16  ;reserving space	

section .code
global _start
_start:
	             
	call _menu     	                             ;Call to print the menu
;--------------------------------------
_menu:                                               ;Menu

  _print:
        IO 1,1,menu,len1                             ;Printing Menu
        IO 0,0,choice,2				     ;Getting choice	
       

	case1 : cmp byte[choice],'1'                 ;comparing choices
		jne case2	                     ;checking whether equal
		call nows			     ;call to non overlapped without string 
		jmp  _print			     ;For looping purpose
       
	case2 : cmp byte[choice],'2'		     ;comparing choices	
		jne case3		             ;checking whether equal
		call now                             ;call to non overlapped with string
		jmp  _print                          ;For looping purpose
	
	case3 : cmp byte[choice],'3'                 ;comparing choices
		jne case4			     ;checking whether equal
		call ows			     ;call to overlapped without string
		jmp _print			     ;For looping purpose
	
	case4 :cmp byte[choice],'4'		     ;comparing choices	
		jne case5			     ;checking whether equal	
		call ow				     ;call to overlapped with string	
		jmp  _print			     ;For looping purpose

	case5 : ;cmp byte[choice],'5'                ;comparing choices
	        ;jne case6			     ;checking whether equal

			IO 1,1,newline,1			;Newline
		mov rax,60			     ;exit statement
		mov rdi,0                            ;  "
		syscall															
 

       ; case6 :
		;IO 1,1,invalid,len2                 ;Printing invalid choice
		;jmp _print			     ;For looping purpose						
    


   ret


nows: 
               
                IO 1,1,source,len3
		
		mov rsi,src
		call print_array
		
		mov rsi,dest
		call print_array
		
		mov rcx,5
		mov rsi,src
		mov rdi,dest
	nextval:
		mov rax,[rsi]
		mov [rdi],rax
		add rsi,8
		add rdi,8
                loop nextval
                
                
                IO 1,1,destination,len3
                
		mov rsi,src
		call print_array
		mov rsi,dest
		call print_array
   ret


now:
		IO 1,1,source,len3
		
		mov rsi,src
		call print_array
		
		mov rsi,dest
		call print_array
		
		cld	
		mov rcx,5	
		mov rsi,src
		mov rdi,dest
		rep movsq
		
		
		IO 1,1,destination,len3
		mov rsi,dest
		call print_array

   ret


ows:
	IO 1,1,source,len3
	
	mov rsi,src
	call print_array
	mov rsi,dest
	call print_array
	 
	 mov rcx,5
	 mov rsi,src+32
	 mov rdi,src+48
nextval2:
	 mov rax,[rsi]
	 mov [rdi],rax
	 sub rsi,8
	 sub rdi,8
	loop nextval2
	
	IO 1,1,destination,len3
	mov rsi,src
	call print_array
	mov rsi,dest
	call print_array
  ret	


ow:
	
	
	IO 1,1,source,len3
	mov rsi,src
	call print_array
        mov rsi,dest
	call print_array
       
        mov rcx,7

        
        mov rsi,src
	mov rdi,src
        sub rdi,16

	rep movsq
	
	IO 1,1,destination,len3
	mov rsi,src
	call print_array
	mov rsi,dest
	call print_array
  ret


print_array:

		
		mov rcx,5
              

	next_ele:
		mov rbx,rsi
		push rcx
		push rsi 
		call display
 
                IO 1,1,space,1               
 
                pop rsi
		
		mov rbx,[rsi]
		
		push rsi               
		call display

		IO 1,1,endline,1

		pop rsi
                pop rcx
		add rsi,8
		loop next_ele 
                 
  		IO 1,1,endline,1
                	

    ret


display:
		mov rsi,temp
		mov rcx,16
	next:	rol rbx,4
		mov rax,rbx
		and rax,0FH
		cmp rax,09H
		jbe add_30
		add rax,07H
	add_30:
		add rax,30H
		mov [rsi],rax
		inc rsi
		loop next
		IO 1,1,temp,16
  ret
;------------------------------------
