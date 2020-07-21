#ifndef _UART_H
#define _UART_H

#include "common.h"

void uart_putchar(u8 dat);
void uart_putstr(u8 *str);
void rec_struct_init();
void uart_get_data();
void uart_rec_data_add(u8 dat);
void spilt_str();
#endif