#ifndef _UART_H_
#define _UART_H_

#include <stdint.h>

extern uint8_t bt_uart_one;

extern void bt_trans(uint8_t* data);
extern void bt_color_change(void);

#endif // _UART_H_
