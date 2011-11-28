// attiny45
// 6 LEDs charlieplexed on pins 5, 6, 7
// button on pin 3
// phototransistor on pin 2 (w/ 49.9kohm)
// Vcc = 3V

#include <avr/io.h>
#include <util/delay.h>

void main(void) __attribute__ ((noreturn));  //http://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html

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
	PORTB = led_out[2];
	//~ DDRB = ( 1<<LINE_C | 1<<LINE_B & ~(1<<LINE_A)); //LED 2
	//~ PORTB = ( 1<<LINE_C & ~(1<<LINE_B)); //LED 2
}  

void leds_off() {
	DDRB = 0;
	PORTB = 0;	
}

void main(void) {
	
	while (1) {
	//~ DDRB = ( 1<<LINE_C | 1<<LINE_B & ~(1<<LINE_A)); //LED 2
	//~ PORTB = ( 1<<LINE_C & ~(1<<LINE_B)); //LED 2
	//~ led_delay();
	//~ DDRB = led_dir[1];
	//~ PORTB = led_out[1];
	char led;
	led = 2;
	led_delay();
	light_led(led);
	led_delay();
		// cycle();
		//~ char az;
		//~ char bz;
		//~ char cz;
		//~ az = pins[2];
		//~ bz = pins[(2+1)%3];
		//~ cz = pins[(2+2)%3];
		//~ set(led_port, az);
		//~ clear(led_port, bz);
		//~ output(led_direction, az);
		//~ output(led_direction, bz);
		//~ input(led_direction, cz);
		//~ led_delay();		
	
		//set(led_port, pins[0]);
		//clear(led_port, pins[(0+1)%3]);
		//output(led_direction, pins[0]);
		//output(led_direction, pins[(0+1)%3]);
		//led_delay();
		//input(led_direction, pins[0]);
		//input(led_direction, pins[(0+1)%3]);

	}
}
