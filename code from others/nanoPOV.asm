;************************************************************************
;*									*
;*									*
;*	Persistance of Vision  with a simple LED row			*
;*	Activation of LEDs is timer interrupt controlled		*
;*	Charlieplexing is used to control 8 LEDs via 4 ports		*
;*									*
;************************************************************************

.include "tn25def.inc"


;constants
.equ cycle_time	=50	; sets pixel frequency
			; Timing considerations:

			; Controller is run in default mode: 8 MHz, CKDIV set, resulting in 1 MHz

			; POV is moved with approx. 1 m/s

			; to get equal LED distances in X & Y direction we have to light up 
			; 400 lines per meter (i.e. 400 times x 8 LEDs per second)

			; so 1 MHz/3200 is the interrupt frequency = 312 cycles

			; with an 8bit timer/counter we need to use the prescaler to get there,
			; but a division by 8 will do

			; this means the timer must be set to interrupt at 39 (39x8 = 312)

			; Duty cycle can be something like 1/10

.equ on_time	=cycle_time/10
.equ display_data_size	=11

;defines
.def tmp	=R16	; all purpose register

.def bit_ct	=R17	; pixel counter (0 - 7)
.def byte_ct	=R18	; line counter	(0 - length(image))
.def data	=R15





;***************************************************************************
;*									   *
;*	Code start							   *
;*									   *
;***************************************************************************


; Interrupt vector table

.cseg

.org 0
	rjmp	reset

.org OC0Aaddr
	rjmp int_OC0A

.org OC0Baddr
	rjmp int_OC0B
	

;************************************************************************	
; Reset Routine: Initialise Device
;************************************************************************	

.org INT_VECTORS_SIZE

reset:

ldi	tmp, 0		; Set PortB Input
out	DDRB, tmp

ldi	tmp, 0b00000010	; set timer 0 to CTC mode
out	TCCR0A, tmp

ldi	tmp, 0b00000010	; set prescaler to /8
out	TCCR0B, tmp

ldi	tmp, cycle_time	; set frequency
out	OCR0A, tmp

ldi	tmp, on_time	; set duty cycle
out	OCR0B, tmp

ldi	tmp, 0b00011000	; enable output compare ints
out	TIMSK, tmp

ldi	byte_ct, display_data_size
ldi	bit_ct, 8

sei			; allow interrupts

loop:
rjmp loop




;************************************************************************	
; Int Routine: Deactivate LEDs
;************************************************************************	

int_OC0B:


ldi	tmp, 0		; Set PortB Input
out	DDRB, tmp


reti


;************************************************************************	
; Int Routine: Activate LED as needed
;************************************************************************	

int_OC0A:

cpi	bit_ct, 8			; new byte?
brne	bitout				; no: jump

					; calculate table address
ldi	ZH, high(display_data<<1)
ldi	ZL, low(display_data<<1)
					
mov	tmp, byte_ct
lsl	tmp
add	ZL, tmp
clr	tmp
adc	ZH, tmp
	

lpm	data, Z				; load from program memory table
clr	bit_ct

inc	byte_ct				; last byte?
cpi	byte_ct, display_data_size
brne	bitout

clr	byte_ct				; yes: reset byte counter


bitout:

lsr	data
brcc	end_int_OC0A			; current bit is 0: reti

mov	tmp, bit_ct
rcall	set_led

end_int_OC0A:

inc	bit_ct
reti





; Subroutine to activate an LED
; LED number in tmp

set_led:
ldi	ZH, high(LED_lookup<<1)
ldi	ZL, low(LED_lookup<<1)
lsl	tmp			; tmp * 2
add	ZL, tmp			; search in table
clr	tmp
adc	ZH, tmp


lpm	tmp, Z+			; set port registers
out	DDRB, tmp
lpm	tmp, Z+
out	PORTB, tmp

ret


; Table contains DDR and PORT values for LEDs to activate

LED_lookup:	
.db 0b00001001, 0b00000001
.db 0b00001001, 0b00001000
.db 0b00000011, 0b00000010
.db 0b00000011, 0b00000001
.db 0b00000110, 0b00000100
.db 0b00000110, 0b00000010
.db 0b00001100, 0b00001000
.db 0b00001100, 0b00000100



display_data:

; data get padded, so half the space is wasted. OTOH only short patterns are sensible and there
; is plenty space...

; Arrow
.db 0b00000000
.db 0b00111100
.db 0b00111100
.db 0b00111100
.db 0b00111100
.db 0b11111111
.db 0b01111110
.db 0b00111100
.db 0b00011000
.db 0b00000000
.db 0b00000000


/*

; Triangle
.db 10
.db 0b00000001
.db 0b00000011
.db 0b00000111
.db 0b00001111
.db 0b00011111
.db 0b00111111
.db 0b01111111
.db 0b11111111
.db 0b00000000
.db 0b00000000



; Smilie
.db 0b00111100
.db 0b01000010
.db 0b10010101
.db 0b10100001
.db 0b10100001
.db 0b10010101
.db 0b01000010
.db 0b00111100
.db 0b00000000
.db 0b00000000



; Arrow
.db 0b00111100
.db 0b00111100
.db 0b00111100
.db 0b00111100
.db 0b11111111
.db 0b01111110
.db 0b00111100
.db 0b00011000
.db 0b00000000
.db 0b00000000



; Heart
.db 0b00001110
.db 0b00010001
.db 0b00100001
.db 0b01000010
.db 0b10000100
.db 0b01000010
.db 0b00100001
.db 0b00010001
.db 0b00001110
.db 0b00000000
.db 0b00000000
.db 0b00000000
.db 0b00000000
.db 0b00000000
.db 0b00000000




; HALLO
.db 0b01111111
.db 0b00001000
.db 0b00001000
.db 0b00001000
.db 0b01111111
.db 0b00000000
.db 0b01111000
.db 0b00010110
.db 0b00010001
.db 0b00010110
.db 0b01111000
.db 0b00000000
.db 0b01111111
.db 0b01000000
.db 0b01000000
.db 0b01000000
.db 0b00000000
.db 0b01111111
.db 0b01000000
.db 0b01000000
.db 0b01000000
.db 0b00000000
.db 0b00011100
.db 0b00100010
.db 0b01000001
.db 0b01000001
.db 0b00100010
.db 0b00011100
.db 0b00000000
.db 0b00000000
.db 0b00000000
.db 0b00000000

*/

