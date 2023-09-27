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

;This part was used to turn on and off LED1. I leave it here for reference.
;init:
;			bis.b	#BIT6, &P4DIR				; set P4DIR(6) to OUTPUT
;			bic.b	#LOCKLPM5, &PM5CTL0			; turn on digital I/O
;
;main:
;			bis.b	#BIT6, &P4OUT			; turn on LED1 which is Port 4 Bit 6
;			bic.b	#BIT6, &P4OUT			; turn off LED1 by clearing
;
;			jmp main
;			nop

init:
			bis.b	#BIT6, &P4DIR			; set P4DIR to OUTPUT. P4DIR(6) is LED1
			bic.b	#BIT6, &P4OUT			; set initial value of LED1 to be off

			bic.b	#BIT5, &P4DIR			; set P4(5) as input. P4(5) = switch 1.
			bis.b	#BIT5, &P4REN			; enable pull up/down resistor on P4(1), which corresponds to switch 1. This essentially makes voltage high (1) when switch is open, and makes voltage low (0) when switch is closed (i.e. we press the switch)
			bis.b	#BIT5, &P4OUT			; set resistor as pull up (refering to the family user guide, we see that it is P4DIR=0 (input), P4REN=1 (configured pull up/down resistor, P4OUT=1 (pull up resistor chosen)

			bic.b	#LOCKLPM5, &PM5CTL0

main:
poll_s1:
			bit.b	#BIT5, &P4IN			; bit test to see if P4(5) is a 1 or not
			jnz		poll_s1

toggle:
			xor.b	#BIT6, &P4OUT			; toggle LED 1

			mov.w	#0FFFh, R4

delayLoopToLetHumanRemoveFinger:
			dec.w	R4
			jnz 	delayLoopToLetHumanRemoveFinger



			jmp		main
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
            
