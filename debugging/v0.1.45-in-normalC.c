// attiny45
// 6 LEDs charlieplexed on pins 5, 6, 7
// button on pin 3
// phototransistor on pin 2 (w/ 49.9kohm)
// Vcc = 3V

#include <stdio.h>
#include <time.h>

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds*1000000 + clock();
    while (goal > clock());
}

//~ void main(void) __attribute__ ((noreturn));  //http://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html

#define LINE_A 0
#define LINE_B 1
#define LINE_C 2

	char DDRB;
	char PORTB;
	
//DDRB direction config for each LED (1 = output) //i/o
const char led_dir[6] = {
  ( (1<<LINE_B | 1<<LINE_A) & ~(1<<LINE_C)), //LED 0
  ( (1<<LINE_A | 1<<LINE_B) & ~(1<<LINE_C)), //LED 1
  ( (1<<LINE_C | 1<<LINE_B) & ~(1<<LINE_A)), //LED 2
  ( (1<<LINE_B | 1<<LINE_C) & ~(1<<LINE_A)), //LED 3
  ( (1<<LINE_A | 1<<LINE_C) & ~(1<<LINE_B)), //LED 4
  ( (1<<LINE_C | 1<<LINE_A) & ~(1<<LINE_B)), //LED 5 
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

void light_led(int led_num) { //led_num must be from 0 to 19
	sleep(1);
	printf("led_num. %d \n", led_num);
	printf("ddrb. %d portb. %d", DDRB, PORTB);
	//~ printf("%c",led_num);
	DDRB = led_dir[led_num];
	PORTB = led_out[led_num];
	//~ printf("this is a test. %d \n", led_num);
	//~ DDRB = ( 1<<LINE_C | 1<<LINE_B & ~(1<<LINE_A)); //LED 2
	//~ PORTB = ( 1<<LINE_C & ~(1<<LINE_B)); //LED 2
}  

void leds_off() {
	DDRB = 0;
	PORTB = 0;
}

int main(void) {
	leds_off();
	while (1) {
	int i = 97;
	printf("testint %d", i);
	int led;
	led = 4;
	light_led(led);
	
	}
	return 0;
}
