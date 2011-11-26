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
#define led_delay() _delay_ms(100) // LED delay

#define led_port PORTB
#define led_direction DDRB
#define ledA (1 << PB0)
#define ledB (1 << PB1)
#define ledC (1 << PB2)

void main(void) {
	while (1) {
		set(led_port, ledA);
		clear(led_port, ledB);
		output(led_direction, ledA);
		output(led_direction, ledB);
		led_delay();
		input(led_direction, ledA);
		input(led_direction, ledB);
	}
}
