;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer

;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
main:
			mov.b	#255, R8
			mov.b	#1, R9
			add.b	R8, R9

			mov.b	#-1, R10	; This will appear as 255 (0x0000FF) in the registers because -1 decimal is #0FFh in two's complement. And when moved into the register, they will simply read it as an unsigned binary number.
			add.b	#1, R10

;----------------------------------------------
; ADDC part
;----------------------------------------------

			mov.w	#Var1, R4	; brings in the address pointers for Var1, Var2, and Sum12. Because Var1, Var2, Sum12 are pointers and their immediate values are addresses.
			mov.w	#Var2, R5
			mov.w	#Sum12, R6

			mov.w	0(R4), R7	; lower 16 bits of the first operand FFFFh
			mov.w	0(R5), R8	; lower 16 bits of the second operand 2222h
			add.w	R7, R8		; adding with the lower 16 bits and it will generate a carry
			mov.w	R8, 0(R6)	; put the result of lower 16 bits and put that into R6 with zero offset

			mov.w	2(R4), R7
			mov.w	2(R5), R8
			addc.w	R7, R8		; add upper 16 bits with carry
			mov.w	R8, 2(R6)

;----------------------------------------------
; INV instructions
;----------------------------------------------
			mov.b	#10101010b, R4
			inv.b	R4

;----------------------------------------------
; Rotate instructions
;----------------------------------------------
			mov.b	#1, R4
			clrc				; Clearing carry bit
			rla.b	R4			; Rotate left arithmetically, where a simple 0 is added in from the right, instead of the carry
			rla.b	R4
			rla.b	R4
			rla.b	R4
			rla.b	R4
			rla.b	R4
			rla.b	R4
			rla.b	R4
			rla.b	R4


;----------------------------------------------
; Overflow-based jump instructions
;----------------------------------------------
init:
			mov.b	#0, R4

main1:
			mov.b	#-128, R5
			cmp.b	#1, R5		; This sets the status bits in SR, and then now we can run conditional jump expressions which are emulated instructions that will utlize those status bits

			jge		ItIsGreaterOrEqual
			jl		ItIsLessThan

ItIsGreaterOrEqual:
			mov.b	#1, R4
			jmp		main1


ItIsLessThan:
			mov.b	#2, R4
			jmp		main1


			jmp		main
			nop


;----------------------------------------------
; Memory allocation for the ADDC part
;----------------------------------------------
			.data				; Store global, static variables in RAM, and retain it.
			.retain

Var1:		.long	0E371FFFFh
Var2:		.long	11112222h
Sum12:		.space	4			; .space is used to reserve a block of memory of a specified size. Here we reserve 4 bytes worth of memory.


;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
