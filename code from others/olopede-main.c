#include <avr/io.h>
#include <avr/eeprom.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

void main(void) __attribute__ ((noreturn)); 

/*void delay(int t){*/
/*    for(; t; t--){*/
/*        for(int i = 1; i; i++);*/
/*    }*/
/*}*/

#define B5(x)   ((x&0b00000001)?2:0)  \
                 +((x&0b00000010)?4:0)  \
                 +((x&0b00000100)?8:0)  \
                 +((x&0b00001000)?16:0)  \
                 +((x&0b00010000)?1:0) \

#define IMGLEN   55
#define DELAY    2
#define CYCLES   2

#define sei()  asm volatile ("sei" ::)
#define cli()  asm volatile ("cli" ::)


const static uint8_t image[IMGLEN] = { 
B5(0b01110), 
B5(0b11111), 
B5(0b10001), 
B5(0b10001), 
B5(0b11111), 
B5(0b01110), 
B5(0b00000), 
B5(0b00000), 
B5(0b11111), 
B5(0b11111), 
B5(0b10000), 
B5(0b10000), 
B5(0b10000), 
B5(0b00000), 
B5(0b00000), 
B5(0b01110), 
B5(0b11111), 
B5(0b10001), 
B5(0b11111), 
B5(0b01110), 
B5(0b00000), 
B5(0b00000), 
B5(0b11111), 
B5(0b11111), 
B5(0b00101), 
B5(0b00111), 
B5(0b00010), 
B5(0b00000), 
B5(0b00000), 
B5(0b11111), 
B5(0b11111), 
B5(0b10101), 
B5(0b10101), 
B5(0b10001), 
B5(0b00000), 
B5(0b00000), 
B5(0b11111), 
B5(0b11111), 
B5(0b10001), 
B5(0b11011), 
B5(0b01110), 
B5(0b00000), 
B5(0b00000), 
B5(0b11111), 
B5(0b11111), 
B5(0b10101), 
B5(0b10101), 
B5(0b10001),
B5(0b00000), 
B5(0b00000), 
B5(0b00000), 
B5(0b00000), 
B5(0b00000), 
B5(0b00000), 
B5(0b00000), 
B5(0b00000), 
B5(0b00000), 
};

uint16_t eepromWord __attribute__((section(".eeprom")));


void main(void){
    uint8_t x;
    unsigned int cycle;
    
    /* Following code graciously stolen from EMSL (Menorah project) */
    /* http://www.evilmadscientist.com/article.php/ledholicycle */

    
    // Read cycle value from eeprom, increment, and cut off at 1
    if ( eeprom_read_word(&eepromWord) == 0xffff)
	    cycle = 0U;
    else	
	    cycle = (uint8_t) (eeprom_read_word(&eepromWord)) ;
	    	
    cycle++;
	
    if (cycle >= CYCLES)	
	    cycle = 0U;

    eeprom_write_word(&eepromWord, (uint8_t) cycle);
    
    
    if (cycle % 2 == 0){
        // Shut off
        MCUCR &= ~0x3 << SM0;
        MCUCR |= 0x2 << SM0;     // select power down sleep mode
        MCUCR |= 1 << SE; 
        asm volatile ("sleep" ::);
        DDRB = 0xff;
        PORTB = 'U';
        while(1);
    }
    
    DDRB = 0xff;
    
    while(1){
        for(x = 0; x < IMGLEN; x++){
            PORTB = image[x];
            _delay_ms(2);
        }
    }
}
