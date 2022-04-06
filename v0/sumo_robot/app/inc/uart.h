#ifndef INT_UART_H
#define INT_UART_H

#include "stm8s.h"
void uart1_init(void);
void send_char(char c);
void send_str(char str[]);
char get_char(void);

#endif