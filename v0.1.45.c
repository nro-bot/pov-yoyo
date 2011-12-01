// attiny45
// 6 LEDs charlieplexed on pins 5, 6, 7
// button on pin 3
// phototransistor on pin 2 (w/ 49.9kohm)
// Vcc = 3V

#include <avr/io.h>
#include <util/delay.h>

#define led_delay() _delay_us(2000) // LED delay

#define LINE_A 0
#define LINE_B 1
#define LINE_C 2
#define IMGLEN 8

#define B3(x)	((x&0b00000001)?0:0)  \
                 +((x&0b00000010)?2:0)  \
                 
#define B5(x)   ((x&0b00000001)?0:0)  \
                 +((x&0b00000010)?1:0)  \
                 +((x&0b00000100)?2:0)  \
                 +((x&0b00001000)?3:0)  \
                 +((x&0b00010000)?4:0) \
                 +((x&0b00010000)?5:0) \
                 
//DDRB direction config for each LED (1 = output) //i/o
const char led_dir[6] = {
  ( 1<<LINE_B | 1<<LINE_A & ~(1<<LINE_C)), //LED 0
  ( 1<<LINE_A | 1<<LINE_B & ~(1<<LINE_C)), //LED 1
  ( 1<<LINE_C | 1<<LINE_B & ~(1<<LINE_A)), //LED 2
  ( 1<<LINE_B | 1<<LINE_C & ~(1<<LINE_A)), //LED 3
  ( 1<<LINE_A | 1<<LINE_C & ~(1<<LINE_B)), //LED 4
  ( 1<<LINE_C | 1<<LINE_A & ~(1<<LINE_B)), //LED 5 
};

//PORTB output config for each LED (1 = High, 0 = Low) //hi/lo
const char led_out[6] = {
  ( 1<<LINE_B & ~(1<<LINE_A)), //LED 0
  ( 1<<LINE_A & ~(1<<LINE_B)), //LED 1
  ( 1<<LINE_C & ~(1<<LINE_B)), //LED 2
  ( 1<<LINE_B & ~(1<<LINE_C)), //LED 3
  ( 1<<LINE_A & ~(1<<LINE_C)), //LED 4  
  ( 1<<LINE_C & ~(1<<LINE_A)), //LED 5
};

                 
//~ const static uint8_t image[4] = {
	//~ B3(0b00), 
	//~ B3(0b10), 
	//~ B3(0b11), 
	//~ B3(0b00),
//~ };

const static uint8_t image[IMGLEN] = {
	B5(0b00000),
	B5(0b01110),
	B5(0b11111),
	B5(0b10001),
	B5(0b10001),
	B5(0b11111),
	B5(0b01110),
	B5(0b00000),
}; 

void light_led(char led_num) { //led_num must be from 0 to 19
	DDRB = led_dir[led_num];
	PORTB = led_out[led_num];
	_delay_us(50);
}; 

void leds_off() {
	DDRB = 0;
	PORTB = 0;
};

void flash_test() {
	for(int x=0; x < 6; x++){
		light_led(x);
	}
};

int main(void) {
	while (1) {
		flash_test();
		//~ for(int x = 0; x < IMGLEN; x++){
			//~ light_led( image[x] );
		//~ }
	}
	return 0;
}
