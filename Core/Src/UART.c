#include "UART.h"

#include <string.h>

#include "main.h"
#include "LED.h"

// data ring buffer
uint8_t bt_uart_data_arr[50];
// inturrupt data
uint8_t bt_uart_one;

uint8_t bt_uart_i_index, bt_uart_o_index;


// bt data check flag
// if data come led control on
uint8_t bt_data_flag = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart3)
	{
		bt_uart_data_arr[bt_uart_i_index++] = bt_uart_one;
		
		bt_data_flag = 1;
		
		if(bt_uart_i_index >= 50)
		{
			bt_uart_i_index = 0;
		}
		HAL_UART_Receive_IT(&huart3, &bt_uart_one, 1);
	}
}

void bt_trans(uint8_t* data)
{
	HAL_UART_Transmit(&huart3, data, strlen((char*)data),100);
}


// bt command check array
uint8_t bt_command_arr[20];
uint8_t bt_com_index = 0;

// '/' is command end char
uint8_t bt_com_end_flag = 0;



// if bt data come
// data check and led color change
// bt protocol
// color | num | bright | /
void bt_color_change(void)
{
	
	if(bt_uart_i_index != bt_uart_o_index)
	{
		bt_command_arr[bt_com_index] = bt_uart_data_arr[bt_uart_o_index++];
		
		if(bt_uart_o_index >= 50)
		{
			bt_uart_o_index = 0;
		}
		
		if(bt_command_arr[bt_com_index] == '/')
		{
			bt_com_end_flag = 1;
		}
		
		bt_com_index++;
		
		if(bt_com_index >= 20)
		{
			bt_com_index = 0;
		}
	}
	
	if( bt_uart_i_index == bt_uart_o_index)
	{
		if(bt_com_end_flag)
		{
			bt_com_end_flag = 0;
			
			if(bt_command_arr[0] != 'c')
			{
				led_on_color(bt_command_arr[0]);
			}
			else
			{
				for(uint8_t i = 0; i < LED_NUM; i++)
				{
					led_set(i,bt_command_arr[1],bt_command_arr[2],bt_command_arr[3]);
				}
				
			}
			
			memset(bt_command_arr,0,sizeof(bt_command_arr));
			bt_com_index = 0;
			
			led_send();
		}
	}
}
