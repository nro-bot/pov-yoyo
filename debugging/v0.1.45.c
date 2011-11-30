/*
 * AVRGCC1.c
 *
 * Created: 11/28/2011 10:13:52 AM
 *  Author: Kai Ouyang
 */ 

// attiny45
// 6 LEDs charlieplexed on pins 5, 6, 7
// button on pin 3
// phototransistor on pin 2 (w/ 49.9kohm)
// Vcc = 3V

#include <avr/io.h>
#include <util/delay.h>

#define led_delay() _delay_ms(50) // LED delay

#define LINE_A 0
#define LINE_B 1
#define LINE_C 2

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

void light_led(char led_num) { //led_num must be from 0 to 19
	DDRB = led_dir[led_num];
	PORTB = led_out[led_num];
}  

void leds_off() {
	DDRB = 0;
	PORTB = 0;
}

int main(void) {
	char led = 5;
	while (1) {
	//DDRB = ( 1<<LINE_C | 1<<LINE_B & ~(1<<LINE_A)); //LED 2
	//PORTB = ( 1<<LINE_C & ~(1<<LINE_B)); //LED 2
	//DDRB = led_dir[1];
	//PORTB = led_out[1];
	led_delay();
	light_led(led);
	led_delay();
	}
return 0;
}
