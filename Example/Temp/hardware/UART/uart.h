#ifndef _UART_H
#define _UART_H

#include "common.h"

void uart_putchar(u8 dat);
void uart_putstr(u8 *str);
void rec_struct_init();
void uart_get_data();
void uart_rec_data_add(u8 dat);
void spilt_str();
char str_cmp_fuck(u8 *s_a,u8 *s_b,u8 *s_c);
#endif