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
#define ledA (1 << PB0)
#define ledB (1 << PB1)
#define ledC (1 << PB2)
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
		
		
	}
		output(led_direction, ledC);
		output(led_direction, ledA);
		input(led_direction, ledB);
		
		set(led_port, ledC);
		clear(led_port, ledA);

		led_delay();
		
	for (i = 0; i < 2; i++) {
		b = pins[i];
		a = pins[(i+1)%(3)];
		c = pins[(i+2)%(3)];

		output(led_direction, a);
		output(led_direction, b);
		input(led_direction, c);
		
		set(led_port, a);
		clear(led_port, b);

		led_delay();
		
		//~ input(led_direction, a);
		//~ input(led_direction, b);
		//~ set(led_port, ledA);
		//~ clear(led_port, ledB);
		//~ output(led_direction, ledA);
		//~ output(led_direction, ledB);
		//~ input(led_direction, ledC);
		//~ led_delay();
		//~ input(led_direction, ledA);
		//~ input(led_direction, ledB);

	}
		output(led_direction, ledC);
		output(led_direction, ledA);
		input(led_direction, ledB);
		
		set(led_port, ledA);
		clear(led_port, ledC);

		led_delay();		
}

void main(void) {
	
	while (1) {
		cycle();
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
