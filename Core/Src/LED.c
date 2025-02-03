#include "LED.h"

#include "main.h"
#include "UART.h"

uint8_t led_num = LED_NUM;

uint16_t led_buf[24 * LED_NUM +50];




void led_set(uint8_t n, uint8_t r, uint8_t g, uint8_t b)
{
	if(n > LED_NUM)
	{
		n = LED_NUM;
	}
			
	for(uint8_t i = 0; i<8; i++)
	{
		if(r & 0x80)
		{
			led_buf[n * 24 + i+8] = LED_HIGH;
		}
		else
		{
			led_buf[n * 24 + i+8] = LED_LOW;
		}
		r <<= 1;
		
		if(g & 0x80)
		{
			led_buf[n * 24 + i] = LED_HIGH;
		}
		else
		{
			led_buf[n * 24 + i] = LED_LOW;
		}
		g <<= 1;
		
		if(b & 0x80)
		{
			led_buf[n * 24 + i+16] = LED_HIGH;
		}
		else
		{
			led_buf[n * 24 + i+16] = LED_LOW;
		}
		b <<= 1;
	}

}


void led_send(void)
{
	
		HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, (uint32_t*)led_buf, 24 * LED_NUM + 50);
		HAL_Delay(1);
		HAL_TIM_PWM_Stop_DMA(&htim2,TIM_CHANNEL_2);
}


void search_color(uint8_t red, uint8_t green, uint8_t blue,uint8_t send)
{
	for(uint8_t i = 0; i < led_num; i++)
			{
				led_set(i,red,green,blue);
			}
	
	if(send)
		led_send();
}


void led_off(void)
{
	for(uint8_t i =0; i < led_num; i++)
	{
		led_set(i,0,0,0);
	}
	led_send();
}

void led_on_color(char a)
{
	
	switch(a)
	{
		case 'r': //red
			for(uint8_t i = 0; i < led_num; i++)
			{
				led_set(i,255,0,0);
			}
		break;
			
		case 'g': //green
			for(uint8_t i = 0; i < led_num; i++)
			{
				led_set(i,0,255,0);
			}
		break;
		
		case 'b': //blue
			for(uint8_t i = 0; i < led_num; i++)
			{
				led_set(i,0,0,255);
			}
		break;
		
		case 'y': // yellow
			for(uint8_t i = 0; i < led_num; i++)
			{
				led_set(i,255,255,0);
			}
		break;
					
		case 'p': //purple
			for(uint8_t i = 0; i < led_num; i++)
			{
				led_set(i,255,0,255);
			}
		break;
			
		case 'w': //white
			for(uint8_t i = 0; i < led_num; i++)
			{
				led_set(i,255,255,255);
			}
		break;
		
			
			/*
		case 'R': //rainbow
			for(uint8_t i = 0; i < led_num; i++)
			{
				switch ( i % 3)
				{
					case 0:
						led_set(i,255,0,0);
					break;
					
					case 1:
						led_set(i,0,255,0);
					break;
					
					case 2:
						led_set(i,0,0,255);
					break;
				}
					
			}
		break;	
			*/
		case 'o': //off
			led_off();
		break;
	}
	
}


//size 1 50%, 2 33%, 3 25%, 4 20%, 5 17%
void led_light_down(uint8_t size)
{
	
	if(size == 0)
	{
		return;
	}
	
	size = size +1;
	
	for(uint8_t i = 0; i < LED_NUM; i++)
	{
		if(i % size != 0)
		{
			led_set(i,0,0,0);
		
		}
	}
}

