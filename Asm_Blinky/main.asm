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

init:
			bic.w	#0001h, &PM5CTL0		; Clear location 0 in this particular control register
											; Control registers configure various settings and features of the microcontroller
											; Disable the GPIO power-on HighZ (high impedence == highZ, which basiclly means that the peripheral is effectively disconnected from the circuit)
											; So when we set it to 0, we are basically saying that we want to connect this to the circuit (unlock it)
			bis.b	#01h, &P1DIR			; Setting the P1.0 (port 1 bit 0) as an output. Because it is LED2 on the launchpad board
main:
			xor.b	#01h, &P1OUT			; toggle P1.0 (LED1)
			mov.w	#0FFFFh, R4				; Puts a big number in R4. FFFF is 16 ones, and puts it in R4, which is a really big number when read as an integer.
											; This acts like a delay of like 0.5s before we toggle the P1.0 again. This is while we decrement it.
delay:
			dec.w	R4						; decrement R4
			jnz		delay					; repeat until R4 has been decremented from the super large integer, till it has reached zero

			jmp		main					; the program coming here means that R4 has reached zero. Then we unconditionally jump to main and restart.
			nop


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
            
