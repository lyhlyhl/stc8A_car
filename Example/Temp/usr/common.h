#ifndef COMMON_H
#define COMMON_H
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
#define uint8 unsigned char
#define uint16 unsigned int



#include "stc8.h"
#include "intrins.h"
#include "stdio.h"

#include "delay.h"
#include "i2c.h"
#include "oled.h"

#include "adc.h"
#include "main.h"
#include <math.h>
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_MPU6050.h"
#include "LED.h"
#include "pwm.h"
#include "pca.h"
#include "timer.h"
#include "KEY.h"
#include "PID.h"
#include "uart.h"
#include "Kalman_Filter.h"
#include "timer.h"
#include "string.h"
#include <stdlib.h>
#include "motor_control.h"

extern float dcc;
extern int flag_stop;
extern int sudu;
extern int h1,h2,h3,h4,h5;

extern char flag_angle, flag_speed ,flag_turn;
#endif