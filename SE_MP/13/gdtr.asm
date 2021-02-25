;Problem Statement : Write X86/64 ALP to display the values of GDTR, LDTR, IDTR, TR Registers.
;Author :akm

%macro print 2					
	
	mov rax,1				
	mov rdi,1				
	mov rsi,%1				
	mov rdx,%2				
	syscall					
	
%endmacro					

section .data					

	aim db "Program to display the values of GDTR, LDTR, IDTR, TR Registers",10
	len equ $-aim
	
	rl db 10,"Real mode"					
	rll equ $-rl				
	
	pr db 10,"Protected mode"
	prl equ $-pr
	
	limit db 10,"LIMIT : "
	ll equ $-limit
	
	base db 10,"BASE  : " 
	lb equ $-base 
	
	msg1 db 10,"GDT : "
	msgl1 equ $-msg1
	
	
	msg2 db 10,"LDT : "
	msgl2 equ $-msg2
	
	
	msg3 db 10,"IDT : "
	msgl3 equ $-msg3
	
	msg4 db 10,"TR  : "
	msgl4 equ $-msg4
	
	newline db 0ah
	
section .bss					;uninitialised data section

	gdt resd 1
	    resw 1
	ldt resw 1
	idt resd 1
	    resw 1
	tr resw 1
	
	cr resd 1
	tempbuff resb 4

section .text					;code section
global _start:					;start of program
_start:
	
	print aim,len
	print newline,1
	smsw eax				
	mov dword[cr],eax			
	bt eax,0				
	jnc skp					
 	print pr,prl
	
	jmp nskp
	
	skp:
	
	print rl,rll
	
	nskp:
	
	sgdt [gdt]				
	sldt [ldt]				
	sidt [idt]				
	str  [tr]				
	mov rbx,0				
	
	print msg1,msgl1
	print limit,ll
	mov bx,[gdt+4]				
	call disp
	print base,lb				
	mov bx,[gdt+2]				
	call disp				
	mov bx,[gdt]				
	call disp				
	print newline,1
	
	print msg2,msgl2
	mov bx,[ldt]				;storing ldt in bx			
	call disp
	
	print newline,1
	print msg3,msgl3
	print limit,ll
	mov bx,[idt+4]				
	call disp				
	print base,lb
	mov bx,[idt+2]				
	call disp				
	mov bx,[idt]				
	call disp				
	
	print newline,1
	print msg4,msgl4
	mov bx,[tr]				;storing task register in bx
	call disp				;displaying bx
	
	print newline,1
	mov rax,60				;system exit
	mov rdi,0				;system exit
	syscall					;system interrupt
	
	disp:					;procedure to display 4 characters
		
		mov rsi,tempbuff		;using rsi to store result
		mov rcx,4			;initialising rcx with 4
		mov rax,0
		lp1:
			
			rol bx,4		
			mov al,bl		
			and al,0fh		
			cmp al,9		
			jbe skip		
			add al,7h		
			skip:add al,30h		
			mov [rsi],rax		
			inc rsi			
		
		loop lp1
		
		print tempbuff,4		;printing the 4 digits
	
	ret					;procedure return
