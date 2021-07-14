AN: word 4      */ 4a contatore 
STACK: word 00FF

E: word 45    */ 'E' ASCII 
R: word 52    */ 'R' ASCII 
N: word 4E    */ 'N' ASCII 
S: word 53    */ 'S' ASCII
WARN: word 2E */ '!' ASCII 

START: LDWA R15 STACK
       SPWR R15
       LDWA R7 AN
       LDWI R2 30
       INB R12 0001
       SUB R2 R12   */ Conversione ASCII del coefficente a  
       INB R13 0001
       SUB R2 R13   */ Conversione ASCII del coefficente b 
       INB R14 0001     
       SUB R2 R14   */ Conversione ASCII del coefficente c 
       PUSH R14
       PUSH R13
       PUSH R12
       INB R15 0001   */ Se R15 = 0 setteremo c positivo, Se R15 > 0 setteremo c negativo nel programma 
       SUB R2 R15
       LDWI R9 0           
      
LOOP: POP R0
      JMPZ STOP
      JMPN STOP
      POP R4
      POP R8
      CALL BQ 
      CALL A 
      CALL C
      SUB R9 R15       */ Verifico l'input R15 se Sub restituisce 0 il controllore JMP prosegue chiamando DEF, altrimetni tratta c come negativo in C_NEG 
      JMPNZ C_NEG
      CALL DEF
      HLT

STOP: LDWA R0 E
      LDWA R1 R
      LDWA R2 WARN
      OUTB R0 0000
      OUTB R1 0000
      OUTB R1 0000
      OUTB R2 0000
      OUTB R2 0000
      HLT

SHOW: OUTB R0 0000
      OUTB R4 0000
      OUTB R8 0000
      OUTB R10 0000
      LDWI R12 0
      LDWI R6 0
      LDWI R5 0
      HLT

C_NEG: ADD R3 R10
       CALL SHOW
       HLT

BQ: ADD R4 R10         */ DELTA = b ^2 
       DEC R13
       JMPNZ BQ
       RET LOOP

A: ADD R12 R11   */ A = 4*a 
   DEC R7
   JMPNZ A 
   RET LOOP 

C: ADD R11 R3      /* C= 4*a*c */
   DEC R14
   JMPNZ C
   RET LOOP

DEF: LDWI R1 0      */ Se invece è un numero positivo setta R1= 0 * e restituisce il valore in R10 
     SUB R3 R10     */ Se b^2 - 4ac restituisce un numeor negativo salta ad else 
     JMPN ELSE
     CALL SHOW            

ELSE: NOT R10       */ Quando il risultato del delta è negativo viene convertito con NOT R10 */
      INC R10    /*  +1 --       In positivo */
      INC R1     /* Viene posto R1 = 1 , poichè indica che il risultato in R10 è un numero negativo! */
      LDWA R5 N    /* 'N' (ASCII) */
      LDWA R6 S    /* 'S' (ASCII) */
      OUTB R5 0000  
      OUTB R6 0000 
      CALL SHOW   
      HLT

  




