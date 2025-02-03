#ifndef _LED_H_
#define _LED_H_

#include <stdint.h>

#define LED_HIGH 57
#define LED_LOW 28

#define LED_NUM 21

extern void led_set(uint8_t n, uint8_t r, uint8_t g, uint8_t b);
extern void led_send(void);
extern void led_off(void);
extern void led_on_color(char a);
extern void led_light_down(uint8_t size);
extern void search_color(uint8_t red, uint8_t green, uint8_t blue,uint8_t send);
	
#endif // _LED_H_
