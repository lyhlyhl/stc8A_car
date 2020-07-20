#ifndef _TIMER_H
#define _TIMER_H

#include "common.h"

typedef enum //Ã¶¾Ù´®¿ÚºÅ
{
    UART_1,
    UART_2,
    UART_3,
    UART_4,
}UARTN_enum;

void Timer_uart_init();
void Timer0_init();
void speed_count_init();
float GetCarSpeed(int dat);

void uart_putchar(UARTN_enum uart_n,u8 dat);
void uart_putbuff(UARTN_enum uart_n,u8 *p,u16 len);
void uart_putstr(UARTN_enum uart_n,u8 *str);
#endif