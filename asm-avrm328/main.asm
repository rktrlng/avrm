.NOLIST
.INCLUDE "m328pdef.inc"
.LIST

.DEF counter = R16			; define a var counter

.ORG 0x0000
	RJMP INIT				; on reset, jump to label INIT

INIT:
	LDI R17, 0x20			; set bit 5 in R17 ('value 32')
	OUT DDRB, R17			; Port B is an output port (bit 5)
	CLR counter				; counter = 0

UPDATE:
	OUT	PORTB, counter		; write counter to LED
	INC counter				; increment counter
	RJMP WAIT				; and wait a bit

WAIT:
	LDI R20, 0x00				; Fill Register 20 with 0 and "Load Immediate"
	WAIT_1:
		CPI R20, 0xff			; if (R20 == 255) "Compare Immediate"
		BREQ UPDATE				; "Branch If Equal" to update (but we're not there yet)
		LDI R21, 0x00			; Fill Register R21 with 0
		WAIT_2:
			CPI R21, 0x20		; if (R21 == 0x20)  ==> do WAIT_2 loop 256 * 32 = 8192 times
			BREQ WAIT_1_INC		; R20++
			NOP					; "No Operation Performed"
			INC R21				;  R21++ "Increment R21"
			RJMP WAIT_2			; jump to WAIT_2 (and check if R21 is 0x20 yet)
        ; end WAIT_2
		WAIT_1_INC:
			INC R20				; R20++
			RJMP WAIT_1			; jump to WAIT_1 (and check if R20 is 255 yet)
		; end WAIT_1_INC
    ; end WAIT_1
; end WAIT
