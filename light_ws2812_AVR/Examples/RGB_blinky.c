/*
* Light_WS2812 library example - RGB_blinky
*
* cycles one LED through red, green, blue
*
* This example is configured for a ATtiny85 with PLL clock fuse set and
* the WS2812 string connected to PB4.
*/

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"

struct cRGB led[10];

int main(void)
{

  #ifdef __AVR_ATtiny10__
  CCP=0xD8;		// configuration change protection, write signature
  CLKPSR=0;		// set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)
  #else
  CLKPR=_BV(CLKPCE);
  CLKPR=0;			// set clock prescaler to 1 (attiny 25/45/85/24/44/84/13/13A)
  #endif

  uint64_t i, j, rr, rg, rb, rR, rG, rB, k, d, l, rz;

  for (i=0; i<255; i++) {
    led[0].r = led[0].g = led[0].b = i;
    led[1].r = led[1].g = led[1].b = 255-i;
    ws2812_setleds(led,3);
    _delay_ms(3);
  }

  for (i=255; i>0; i--) {
    led[0].r = led[0].g = led[0].b = i;
    led[1].r = led[1].g = led[1].b = 255-i;
    ws2812_setleds(led,3);
    _delay_ms(3);
  }

  _delay_ms(100);

  rR = rG = rB = 0;
//  k = 100;
  d = 255;
  l = 64;

  for (i=0; i<30; i++) {
    rz = rand() % 3;

    rr = rand() % l * ((rz+2)%3);
    rg = rand() % l * ((rz+1)%3);
    rb = rand() % l * ((rz)%3);


    for (j=0; j<d;j++){
      led[0].r = ((rr * j / d) + (rR * (d-j) / d));
      led[0].g = ((rg * j / d) + (rG * (d-j) / d));
      led[0].b = ((rb * j / d) + (rB * (d-j) / d));
      led[1].r = 127-led[0].r;
      led[1].g = 127-led[0].g;
      led[1].b = 127-led[0].b;
      ws2812_setleds(led,3);
      _delay_ms(5);
    }

    rR = rr;
    rG = rg;
    rB = rb;
    _delay_ms(100);

  }
  _delay_ms(100000);

  for (i=0; i<255; i++) {
    led[0].r = i;
    led[1].r = i;
    ws2812_setleds(led,3);
    _delay_ms(3);
  }

  for (i=255; i>0; i--) {
    led[0].r = i;
    led[1].r = i;
    ws2812_setleds(led,3);
    _delay_ms(3);
  }

  for (i=0; i<255; i++) {
    led[0].r = led[0].b = i;
    led[1].r = led[1].b = i;
    ws2812_setleds(led,3);
    _delay_ms(3);
  }

  for (i=255; i>0; i--) {
    led[0].r = led[0].b = i;
    led[1].r = led[1].b = i;
    ws2812_setleds(led,3);
    _delay_ms(3);
  }

  for(i=0; i<100; i++) {
    led[0].r = rand() % 256;
    led[0].g = rand() % 256;
    led[0].b = rand() % 256;
    led[1].r = rand() % 256;
    led[1].g = rand() % 256;
    led[1].b = rand() % 256;
    ws2812_setleds(led,3);
    _delay_ms(30);
  }

//  while(1){
  for(i=0; i<100; i++) {
    led[0].r = 255 * rand() % 2;
    led[0].g = 255 * rand() % 2;
    led[0].b = 255 * rand() % 2;
    led[1].r = 255 * rand() % 2;
    led[1].g = 255 * rand() % 2;
    led[1].b = 255 * rand() % 2;
    ws2812_setleds(led,3);
    _delay_ms(30);
  }

  for(i=0; i<10000; i++) {
    j = 1ULL << (i % 48);
    led[0].r = ( j          ) ;
    led[0].g = ( j     >> 4 ) ;
    led[0].b = ( j     >> 8 ) ;
    led[1].r = ( j / 8 >> 0 ) ;
    led[1].g = ( j / 8 >> 8 ) ;
    led[1].b = ( j / 8 >> 16) ;
    ws2812_setleds(led,3);
    _delay_ms(10);
  }



//  while(1)
  for(i=0; i<100; i++)
  {
    led[0].r=255;led[0].g=00;led[0].b=0;    // Write red to array
    ws2812_setleds(led,2);
    _delay_ms(500);                         // wait for 500ms.

    led[0].r=0;led[0].g=255;led[0].b=0;			// green
    ws2812_setleds(led,1);
    _delay_ms(500);

    led[0].r=0;led[0].g=00;led[0].b=255;		// blue
    ws2812_setleds(led,1);
    _delay_ms(500);
  }
}
