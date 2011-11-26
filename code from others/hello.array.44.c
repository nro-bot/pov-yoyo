//
//
// hello.array.44.c
//
// Charlieplex LED array hello-world
//
// Neil Gershenfeld
// 11/13/10
//
// (c) Massachusetts Institute of Technology 2010
// Permission granted for experimental and personal use;
// license for commercial sale available from MIT.
//

#include <avr/io.h>
#include <util/delay.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define input(directions,pin) (directions &= (~pin)) // set port direction for input 
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set

#define led_delay() _delay_ms(1) // LED delay

#define led_port PORTA
#define led_direction DDRA

#define A (1 << PA1) // row 1
#define B (1 << PA2) // row 2
#define C (1 << PA3) // row 3
#define D (1 << PA4) // row 4
#define E (1 << PA5) // row 5

void flash(uint8_t from, uint8_t to, uint8_t delay) {
   //
   // source from, sink to, flash
   //
   static uint8_t i;
   set(led_port,from);
   clear(led_port,to);
   output(led_direction,from);
   output(led_direction,to);
   for (i = 0; i < delay; ++i)
       led_delay();
   input(led_direction,from);
   input(led_direction,to);
   }

void led_cycle(uint8_t number, uint8_t delay) {
   //
   // cycle through LEDs
   //
   uint8_t i;
   for (i = 0; i < number; ++i) {
      flash(B,A,delay);
      flash(C,A,delay);
      flash(D,A,delay);
      flash(E,A,delay);
      flash(A,B,delay);
      flash(C,B,delay);
      flash(D,B,delay);
      flash(E,B,delay);
      flash(A,C,delay);
      flash(B,C,delay);
      flash(D,C,delay);
      flash(E,C,delay);
      flash(A,D,delay);
      flash(B,D,delay);
      flash(C,D,delay);
      flash(E,D,delay);
      flash(A,E,delay);
      flash(B,E,delay);
      flash(C,E,delay);
      flash(D,E,delay);
      }
   }

int main(void) {
   //
   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //
   // main loop
   //
   while (1) {
      led_cycle(1,100);
      led_cycle(3,20);
      led_cycle(100,1);
      }
   }
