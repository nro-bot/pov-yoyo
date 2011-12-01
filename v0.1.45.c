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
#define IMGLEN 55

//~ #define B3(x)	((x&0b00000001)?0:0)  \
                 //~ +((x&0b00000010)?2:0)  \
                 
//~ #define B5(x)   ((x&0b00000001)?0:0)  \
                 //~ +((x&0b00000010)?1:0)  \
                 //~ +((x&0b00000100)?2:0)  \
                 //~ +((x&0b00001000)?3:0)  \
                 //~ +((x&0b00010000)?4:0) \
                 //~ +((x&0b00010000)?5:0) \
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
void light_led(char led_num) { //led_num [0,5]
	DDRB = led_dir[led_num];
	PORTB = led_out[led_num];
	_delay_us(20);
}; 

const static char bit[5] = {
	0b00001,
	0b00010,
	0b00100,
	0b01000,
	0b10000,
};

void check_led(char bar, int i){
	if (bar & bit[i]) { //which led to light up?
		light_led(i);
	 }
	 else {
		 _delay_us(30);
	 }
};

void B5(char x) {
	for(int j=0; j < 6; j++){
		check_led(x,j);
	};	
};
               
//~ const static uint8_t image[4] = {
	//~ B3(0b00), 
	//~ B3(0b10), 
	//~ B3(0b11), 
	//~ B3(0b00),
//~ };

const static char image[IMGLEN] = {
0b01110, 
0b11111, 
0b10001, 
0b10001, 
0b11111, 
0b01110, 
0b00000, 
0b00000, 
0b11111, 
0b11111, 
0b10000, 
0b10000, 
0b10000, 
0b00000, 
0b00000, 
0b01110, 
0b11111, 
0b10001, 
0b11111, 
0b01110, 
0b00000, 
0b00000, 
0b11111, 
0b11111, 
0b00101, 
0b00111, 
0b00010, 
0b00000, 
0b00000, 
0b11111, 
0b11111, 
0b10101, 
0b10101, 
0b10001, 
0b00000, 
0b00000, 
0b11111, 
0b11111, 
0b10001, 
0b11011, 
0b01110, 
0b00000, 
0b00000, 
0b11111, 
0b11111, 
0b10101, 
0b10101, 
0b10001,
0b00000, 
0b00000, 
0b00000, 
0b00000, 
0b00000, 
0b00000, 
0b00000, 
0b00000, 
0b00000, 
}; 

//~ void light_leds(char led_state) { //led_state is on/off 1 bit per LED	
//~ }; 


void leds_off() {
	DDRB = 0;
	PORTB = 0;
};

void flash_test() {
	for(int x=0; x < 6; x++){
		light_led(x);
		_delay_ms(10);
	}
};

int main(void) {
	while (1) {
		//~ flash_test();
		//~ light_led(3);
		for(int x = 0; x < IMGLEN; x++){
			B5(image[x]);
			leds_off();
			_delay_us(200);
		}
	}
	return 0;
}
