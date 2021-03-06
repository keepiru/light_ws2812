# Makefile to build light_ws2812 library examples
# This is not a very good example of a makefile - the dependencies do not work, therefore everything is rebuilt every time.

# Change these parameters for your device

F_CPU = 8000000
DEVICE = atmega168

# Tools:
CC = avr-gcc

LIB       = light_ws2812
EXAMPLES  = RGB_blinky Chained_writes
DEP		  = ws2812_config.h Light_WS2812/light_ws2812.h

CFLAGS = -g2 -I. -ILight_WS2812 -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) 
CFLAGS+= -Os -ffunction-sections -fdata-sections -fpack-struct -fno-move-loop-invariants -fno-tree-scev-cprop -fno-inline-small-functions  
CFLAGS+= -Wall -Wno-pointer-to-int-cast
#CFLAGS+= -Wa,-ahls=$<.lst

LDFLAGS = -Wl,--relax,--section-start=.text=0,-Map=main.map

all:	$(EXAMPLES) flash

$(LIB): $(DEP)
	@echo Building Library 
	@$(CC) $(CFLAGS) -o Objects/$@.o -c Light_WS2812/$@.c 

$(EXAMPLES): $(LIB) 
	@echo Building $@
	@$(CC) $(CFLAGS) -o Objects/$@.o Examples/$@.c Light_WS2812/$^.c
	@avr-size Objects/$@.o
	@avr-objcopy -j .text  -j .data -O ihex Objects/$@.o $@.hex
	@avr-objdump -d -S Objects/$@.o >Objects/$@.lss

.PHONY:	clean

clean:
	rm -f *.hex Objects/*.o Objects/*.lss

PORT = /dev/ttyUSB0

fuse:
	avrdude -y -P ${PORT} -cbuspirate -pm168 -U lfuse:w:0xe2:m -U hfuse:w:0xd7:m -U efuse:w:0x01:m

flash:
	avrdude -V -y -P ${PORT} -cbuspirate speed=6 -b115200 -pm168 -Uflash:w:RGB_blinky.hex
