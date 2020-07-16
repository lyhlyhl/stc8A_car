#ifndef _TIMER_H
#define _TIMER_H

#include "common.h"

void Timer_uart_init();
void Timer0_init();
void speed_count_init();
float GetCarSpeed(int dat);

#endif