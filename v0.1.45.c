// attiny45
// 6 LEDs charlieplexed on pins 5, 6, 7
// button on pin 3
// phototransistor on pin 2 (w/ 49.9kohm)
// Vcc = 3V

#include <avr/io.h>
#include <util/delay.h>

void main(void) __attribute__ ((noreturn));  //http://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html

#define output(directions,pin) (directions |= pin) // set port direction for output
#define input(directions,pin) (directions &= (~pin)) // set port direction for input 
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define led_delay() _delay_ms(50) // LED delay

#define led_port PORTB
#define led_direction DDRB
// #define LINE_A (1 << PB0)
// #define LINE_B (1 << PB1)
// #define LINE_C (1 << PB2)
#define LINE_A 0
#define LINE_B 1
#define LINE_C 2

//DDRB direction config for each LED (1 = output)
const char led_dir[20] = {
  ( 1<<LINE_B | 1<<LINE_A ), //LED 0
  ( 1<<LINE_A | 1<<LINE_B ), //LED 1
  ( 1<<LINE_C | 1<<LINE_B ), //LED 2
  ( 1<<LINE_B | 1<<LINE_C ), //LED 3
  ( 1<<LINE_A | 1<<LINE_C ), //LED 4
  ( 1<<LINE_C | 1<<LINE_A ), //LED 4 
};

//PORTB output config for each LED (1 = High, 0 = Low)
const char led_out[20] = {
  ( 1<<LINE_B ), //LED 0
  ( 1<<LINE_A ), //LED 1
  ( 1<<LINE_C ), //LED 2
  ( 1<<LINE_B ), //LED 3
  ( 1<<LINE_A ), //LED 4  
  ( 1<<LINE_C ), //LED 5
};

void light_led(char led_num) { //led_num must be from 0 to 19
	DDRB = led_dir[led_num];
	PORTB = led_out[led_num];
}  

void leds_off() {
	DDRB = 0;
	PORTB = 0;	
}
const char pins[] = {ledA,ledB,ledC};
//pins[i];
// cwrite(led1, HIGH); delay(1000);
// led_cycle(){ blink(led1, ontime);}
void cycle(void) {
		char a;
		char b;
		char c;
		int i;
		
	for (i = 0; i < 2; i++) {
		a = pins[i];
		b = pins[(i+1)%(3)];
		c = pins[(i+2)%(3)];

		output(led_direction, a);
		output(led_direction, b);
		input(led_direction, c);
		
		set(led_port, a);
		clear(led_port, b);

		led_delay();
		
		clear(led_port, b);
	}
		output(led_direction, ledC);
		output(led_direction, ledA);
		input(led_direction, ledB);
		
		set(led_port, ledC);
		clear(led_port, ledA);

		led_delay();
		
}

void main(void) {
	
	while (1) {
	light_led(0);
	led_delay();
	light_led(1);
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
