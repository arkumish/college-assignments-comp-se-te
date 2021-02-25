;PROCEDURE FILE                                                              ;SECOND PROGRAM
%include "macro.asm"                                              ;TO INCLUDE MACRO FROM EXTERNAL FILE
global display,read,counting                                       ;GLOBAL VARIABLES
extern scount,ncount,ccount,text,buff,choice,temp                  ;IMPORTED FROM EXTERNAL FILE

;---------------------------------------
display:                                                           ;DISPLAY PROCEDURE
		mov rsi,temp                                       ;MOVING RSI TO TEMP
		mov rcx,16                                         ;SETTING RCX TO 16
	next:	rol rbx,4                                          ;ROTATING RBX BY 4
		mov rax,rbx                                        ;MOVING RBX TO RAX
		and rax,0FH                                        ;FOR LAST 4 BITS
		cmp rax,09H                                        ;COMPARING FOR LESS THAN 9
		jbe add_30                                         ;FOR ASCII CONVERSION
		add rax,07H                                        ;        "
	add_30:                                                      
		add rax,30H                                        ;        "
		mov [rsi],rax                                      ;MOVING RAX FROM RSI TO MOVE VALUE TO TEMP
		inc rsi                                            ;INCREMENT THE RSI
		loop next                                          ;FOR LOOPING PURPOSE
		print temp,16                                      ;PRINTING TEMP
  ret
;---------------------------------------
counting:                                                          ;PROCEDURE FOR COUNTING
        
      	mov rsi,text                                               ;MOVING POINTER TO TEXT
	mov rcx,[buff]						   ;MOVING NUMBER OF CHARACTERS TO RCX
        mov dl,[choice]                                            ;FOR CHOICE COMPARISON

label:                                                             ;LABEL FOR LOOP
     case1: cmp byte[rsi],20H		                           ;COMPARISON WITH ASCII FOR SPACE
            jne case2                                              ;IF NOT EQUAL THAN JUMP
            inc qword[scount]                                      ;ELSE INCREMENT SPACE COUNT
	  
     case2: cmp byte[rsi],10                                       ;COMPARISON WITH ASCII FOR ENDLINE
            jne case3		                                   ;IF NOT EQUAL THAN JUMP
            inc qword[ncount]				           ;ELSE INCREMENT ENDLINE COUNT

     case3: 
            cmp byte[rsi],dl                                       ;COMPARISON WITH ASCII FOR CHARACTER
            jne case4                                              ;IF NOT EQUAL THAN JUMP
            inc qword[ccount]                                      ;ELSE INCREMENT ENDLINE COUNT

     case4: inc rsi                                                ;ELSE INCREMENT RSI
 
     loop label                                                    ;LOOP TO LABEL

ret
;---------------------------------------
  
