%macro display 2				;display macro
	mov rax,1				;mov sys_write in rax
	mov rdi,1				;stdout
	mov rsi,%1				;1st Parameter (Buffer Address)
	mov rdx,%2				;2nd Parameter (Buffer Length)
	syscall					;call to Kernel
%endmacro

%macro read 2					;read macro
	mov rax,0				;mov sys_read in rax
	mov rdi,0				;stdin
	mov rsi,%1				;1st Parameter (Buffer Address)
	mov rdx,%2				;2nd Parameter (Buffer Length)
	syscall					;call to Kernel
%endmacro

%macro fopen 1					;read macro
	mov rax,2				;mov sys_read in rax
	mov rdi,%1				;stdin
	mov rsi,42h				;1st Parameter (Buffer Address)
	mov rdx,0777o				;2nd Parameter (Buffer Length)
	syscall					;call to Kernel
%endmacro

%macro frw 4
	mov rax,%1				;mov sys_read in rax
	mov rdi,%2				;stdin
	mov rsi,%3				;1st Parameter (Buffer Address)
	mov rdx,%4				;2nd Parameter (Buffer Length)
	syscall	
%endmacro

%macro fclose 1					;read macro
	mov rax,3				;mov sys_read in rax
	mov rdi,%1				;stdin
	syscall					;call to Kernel
%endmacro

%macro fdelete 1
	mov rax,87
	mov rdi,%1
	syscall					;call to Kernel
%endmacro
