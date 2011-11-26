PROJECT=./v0.1.45
SOURCES=$(PROJECT).c
#SOURCES=hello.txrx.45.c
MMCU=attiny45
F_CPU = 8000000

CFLAGS=-mmcu=$(MMCU) -Wall -Os -DF_CPU=$(F_CPU)

$(PROJECT).hex: $(PROJECT).out
	avr-objcopy -j .text -O ihex $(PROJECT).out $(PROJECT).c.hex;\
   avr-size --mcu=$(MMCU) --format=avr $(PROJECT).out
 
$(PROJECT).out: $(SOURCES)
	avr-gcc $(CFLAGS) -I./ -o $(PROJECT).out $(SOURCES)
 
program-bsd: $(PROJECT).hex
	avrdude -p t45 -c bsd -U flash:w:$(PROJECT).c.hex

program-dasa: $(PROJECT).hex
	avrdude -p t45 -P /dev/ttyUSB0 -c dasa -U flash:w:$(PROJECT).c.hex

program-avrisp2: $(PROJECT).hex
	avrdude -p t45  -c avrisp2 -U flash:w:$(PROJECT).c.hex

program-usbtiny: $(PROJECT).hex
	avrdude -p t45  -c usbtiny -U flash:w:$(PROJECT).c.hex

program-dragon: $(PROJECT).hex
	avrdude -p t45  -c dragon_isp -U flash:w:$(PROJECT).c.hex
