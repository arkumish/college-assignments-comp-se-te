
.model small

.stack 100
.386
.data

	msg db 10,13,'This is Sine wave$'
	one_eighty dw 180
	scale dw 60
	hundred dw 100
	rint dw 0
	x dw 0

.code
main: 
	    mov ax,@data            		; Initialize DS (needed for .exe-program)
	    mov ds, ax
	    mov ax, 0A000h       	  	; Segment to video memory
	    mov es, ax

	    mov ax,13h
	    int 10h                 		; switch to 320x200 mode

	    mov cx, 0
	    l1:
	    	
	    	    push cx
	    	    call get_cos
		    mov bx, cx
		    call vector_to_memory
		    mov di, ax
		    mov al, 0Fh            		; color
		    mov [es:di], al         		; put pixel
		    pop cx                  		; restore CX
		    inc cx                  		; CX = CX + 1
		    cmp cx, 320             		; right boarder reached?
	    jne l1                 			; no, next degree

	    xor ah, ah
	    int 16h                 		; keyboard (wait for key)
	    mov ax, 3
	    int 10h                 		; go to text mode
	    mov ax, 4C00h
	    int 21h                 		; return to DOS, exit code 0

	    get_cos:                   		; Args: CX = angle (degree!)
		  
		    mov word[x],cx
		    fldpi                   		; ST(0)=Pi
		    fimul word[x]            		; ST(0)=Pi*CX
		    
		    fidiv word[one_eighty] 		; ST(0)=(Pi*CX)/180(degree to rad)
		    fcos                    		; ST(0)=sine (rad)
		    fimul word[scale]      		; ST(0)=sine*scale
		    fild hundred			; ST(0)=100, ST(1)=60*(sin(Pi*CX)/180))
		    fsub st,st(1)			; ST(0)=100-60*SIN((Pi*CX)/180)
		    fist word [rint]       		; store integer with rounding 
		    mov ax, word[rint]     		; AX = Y
	    ret                     		        ; Return: AX = Y (signed!)

	    vector_to_memory:           		; Calculate offset=Y*320+X 
							;Args: BX = X, AX = Y
		    push dx                 		; mul changes dx too
		    mov cx, 320             		; video mode width 
		    mul cx                  		; DX:AX = AX * CX
		    add ax, bx              		; left indentation
		    pop dx
	    ret                     		; Return: AX = offset in memory

	    end   main
