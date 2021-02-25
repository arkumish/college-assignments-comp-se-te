 ;Write a TSR to generate the pattern of the frequency tones by reading the Real Time Clock (RTC). The duration of the each tone is solely decided by the programmer.



.MODEL TINY
.CODE
        ORG 100H                ;START FROM 100H LOCATION
START:  JMP INIT

        TEMPAX DW ?
        TEMPBX DW ?
        TEMPCX DW ?
        TEMPDX DW ?
        TEMPSI DW ?
        TEMPDI DW ?

        TEMPDS DW ?
        TEMPES DW ?
	   TEMP DW 0
        SAVEINT08 DD ?

MYINT08:
	;Reserve memory locations to store the registers and original vector address

        MOV CS:TEMPAX,AX	
        MOV CS:TEMPBX,BX
        MOV CS:TEMPCX,CX
        MOV CS:TEMPDX,DX
        MOV CS:TEMPSI,SI
        MOV CS:TEMPDI,DI
        MOV CS:TEMPDS,DS
        MOV CS:TEMPES,ES


	MOV AH,02H              	;READ CLOCK. RETURNS CH=HH, CL=MM, DH=SS IN BCD
        INT 1AH
	INC CS:TEMP			;for beep
        MOV AX,0B800H           	;BASE ADDRESS OF PAGE-0 OF VIDEO RAM
        MOV ES,AX
        MOV DI,3984             	;OFFSET IN VIDEO RAM WHERE WE WANT TO DISPLAY HH:MM:SS

					;DISPLAYING HH
        MOV BL,02               	;NUMBER OF DIGITS TO DISPLAY
	UP1:
	    	
	    	ROL CH,1               	;ROTATE
        	ROL CH,1               
		ROL CH,1               
		ROL CH,1               
		MOV AL,CH
        	AND AL,0FH
		ADD AL,30H		;CHARACTER BYTE (HOUR)
		MOV AH,17H              ;ATTRIBUTE BYTE (BL R G B I R G B) 00010111
		MOV ES:[DI],AX
		INC DI
		INC DI
		DEC BL
        
        JNZ UP1

					;DISPLAYING BLINKING ':'
        MOV AL,':'
        MOV AH,94H
        MOV ES:[DI],AX

        INC DI
        INC DI

					;DISPLAYING MM
        MOV BL,02               	;NUMBER OF DIGITS TO DISPLAY
	UP2:    
		
		ROL CL,1               	;ROTATE
		ROL CL,1               
		ROL CL,1               
		ROL CL,1               
		MOV AL,CL
		AND AL,0FH
		ADD AL,30H
		MOV AH,17H              ;ATTRIBUTE BYTE (BL R G B I R G B)
		MOV ES:[DI],AX
		INC DI
		INC DI
		DEC BL
		
        JNZ UP2

					;DISPLAYING BLINKING ':'
        MOV AL,':'
        MOV AH,94H
        MOV ES:[DI],AX

        INC DI
        INC DI

					;DISPLAYING SS
        MOV BL,02               	;NUMBER OF DIGITS TO DISPLAY
	UP3: 
	
		ROL DH,1              	;ROTATE
		ROL DH,1               
		ROL DH,1 
		ROL DH,1                             
		MOV AL,DH
		AND AL,0FH
		ADD AL,30H
		MOV AH,17H              ;ATTRIBUTE BYTE (BL R G B I R G B)
		MOV ES:[DI],AX
		INC DI
		INC DI
		DEC BL
		
        JNZ UP3
        
	cmp cs:temp,91				;for 5sec 18.2*5=91
	jne nobeep
	  
	mov cs:temp,00h
       	mov     ax, 1193        ; Frequency number (in decimal)divided 1,193,180 by desired tone here we used 1000Hz
        out     42h, al         ; Output low byte.
        mov     al, ah          ; Output high byte.
        out     42h, al
		
        in      al, 61h         ; Turn on note (get value from
                              ;  port 61h).
        or      al, 00000011b   ; Set bits PB1 and PB0.
        out     61h, al         ; Send new value.
        mov     bx, 25          ; Pause for duration of note.

	pause1:
        	
        	mov     cx, 65535

		pause2:
			dec     cx
		jne     pause2
			dec     bx
	jne     pause1

	in      al, 61h         ; Turn off note (get value from
				;  port 61h).
	and     al, 11111100b   ; Reset bits 1 and 0.
	out     61h, al  

	nobeep:	

		MOV AX,CS:TEMPAX
		MOV BX,CS:TEMPBX
		MOV CX,CS:TEMPCX
		MOV DX,CS:TEMPDX
		MOV SI,CS:TEMPSI
		MOV DI,CS:TEMPDI
		MOV DS,CS:TEMPDS
		MOV ES,CS:TEMPES

        JMP CS:SAVEINT08

INIT:   
	
	CLI
        MOV AH,35H              ;GET VECTOR
        MOV AL,08H              ;OF TYPE 08
        INT 21H                 ;WHICH RETURNS VECTOR ADDRESS IN ES:BX

        MOV WORD PTR SAVEINT08,BX
        MOV WORD PTR SAVEINT08+2,ES

        MOV AH,25H              ;SET VECTOR
        MOV AL,08H              ;OF TYPE 08
        LEA DX,MYINT08          ;ENTRY POINT OF MY ISR STORED IN DS:DX
        INT 21H

        MOV AH,31H              ;TERMINATE AND MAKE RESIDENT
        LEA DX,INIT             ;SIZE OF MEMORY BLOCK
        STI                     ;SET IF
        INT 21H
        
END START
