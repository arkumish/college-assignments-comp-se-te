;Write X86 ALP to find, 
;a) Number of Blank spaces 
;b) Number of lines 
;c) Occurrence of a particular character. 
;Accept the data from the text file. The text file has to be accessed during
;Program_1 execution and write FAR PROCEDURES in Program_2 for the rest of the processing.
;Use of PUBLIC and EXTERN directives is mandatory.
 
;Name : AKM
;Roll Number : 9999
;D.O.P :2019
 
%include "macro.asm"                                           
global scount,ncount,ccount,text,buff,choice,temp               ;GLOBAL VARIABLES
extern display,counting                                         ;IMPORTED FROM EXTERNAL FILE

section .data                                              ;TO DECLARE INITIALIZED DATA
                                                           
m1 db 10,"Enter the filename  : "				  ;MESSAGE 1
l1 equ $-m1								  ;LENGTH OF MESSAGE 1
m2 db 10,"Error opening the file",10					  ;MESSAGE 2
l2 equ $-m2								  ;LENGTH OF MESSAGE 2
m3 db "SPACE COUNT IN FILE :" 							  ;MESSAGE 3
l3 equ $-m3								  ;LENGTH OF MESSAGE 3	
m4 db 10,"NEWLINE COUNT IN FILE :"						  ;MESSAGE 4	
l4 equ $-m4								  ;LENGTH OF MESSAGE 4	
m5 db 10,"CHARACTER COUNT IN FILE :"                                               ;MESSAGE 5
l5 equ $-m5								  ;LENGTH OF MESSAGE 5	

m6 db "ENTER CHARACTER TO SEARCH : "                                                ;MESSAGE 6
l6 equ $-m6								  ;LENGTH OF MESSAGE 6			

m7 db 10                                                                  ;FOR ENDLINE



section .bss                                                     ;FOR UNINITIALIZED DATA
temp resb 16							 ;FOR DISPLAY PROCEDURE							
scount resq 1                                                    ;FOR SPACE COUNT
ncount resq 1							 ;FOR ENDLINE COUNT			
ccount resq 1							 ;FOR CHARACTER COUNT	
filen resq 1						         ;FOR FILENAME LENGTH
filename resb 10					         ;FOR FILENAME
fileh resq 1							 ;FOR FILEHANDLER
choice resb 2						         ;FOR CHOICE OF CHARACTER
text resb 1024							 ;FOR STORING FILES DATA
buff resq 1							 ;STORING THE LENGTH OF FILE			

section .code                                                    ;FOR CODE SECTION
global _start							 ;FOR STARTING POINT 								
_start:
   
   print m1,l1							 ;PRINTING MESSAGE 1				

   scan filename,10                                              ;INPUTTING FILE NAME
   dec rax				                         ;REMOVING ENDLINE FROM FILENAME
   mov [filen],rax                                               ;STORING FILELENGHT IN FILEN
   mov byte[filename+rax],0                                      ;APPENDING 0 AT THE END OF FILE NAME
   
   fopen filename                                                ;OPENING A FILE
   mov [fileh],rax                                               ;GETTING A FILE HANDLER
   cmp rax,0FFFFFFFFFFFFFFFEH                                    ;CHECKING FOR ERROR
   je error                                                      ;JUMP IF EQUAL
   
   fread [fileh],text,1024                                       ;READING THE FILE
   mov [buff],rax                                                ;STORING THE SIZE OF THE FILE
   print text,[buff]                                             ;PRINTING DATA ON SCREEN
   fclose fileh                                                  ;CLOSING THE FILE
   
   print m6,l6                                                   ;PRINTING MESSAGE 6
   scan choice,2                                                 ;GETTING CHOICE OF CHARACTER
 
   call counting                                                 ;COUNTING CHARACTER
   
   print m3,l3                                                   ;PRINTING MESSAGE 3
   mov rbx,[scount]			                         ;DISPLAYING SPACES
   call display                                                  ;   "
   
   print m4,l4                                                   ;PRINTING MESSAGE 4
   mov rbx,[ncount]                                              ;DISPLAYING ENDLINE
   call display                                                  ;   "
   
   print m5,l5                                                   ;PRINTING MESSAGE 5
   mov rbx,[ccount]                                              ;DISPLAYING CHARACTER
   call display                                                  ;   "
   
   print m7,1                                                    ;ENDLINE
      
   jmp exi                                                       ;JUMP TO EXIT THE PROGRAM
   
   error:                                                        ;PRINTING ERROR METHOD
   print m2,l2 
exi:
   exit                                                          ;EXITING THE PROGRAM
