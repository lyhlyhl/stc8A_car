#ifndef ADC_H
#define ADC_H

#include "common.h"

typedef enum
{
    ADC_P10 = 0     , 
    ADC_P11         , 
    ADC_P12         , 
	ADC_P13         , 
    ADC_P14         , 
	ADC_P15         , 
	ADC_P16         , 
	ADC_P17         , 
	
	ADC_P00         , 
	ADC_P01         , 
	ADC_P02         , 
	ADC_P03         , 
	ADC_P04         , 
	ADC_P05         , 
	ADC_P06         , 
} ADCN_enum;




//此枚举定义不允许用户修改
typedef enum
{
	ADC_SYSclk_DIV_2 = 0,
	ADC_SYSclk_DIV_4,
	ADC_SYSclk_DIV_6,
	ADC_SYSclk_DIV_8,
	ADC_SYSclk_DIV_10,
	ADC_SYSclk_DIV_12,
	ADC_SYSclk_DIV_14,
	ADC_SYSclk_DIV_16,
	ADC_SYSclk_DIV_18,
	ADC_SYSclk_DIV_20,
	ADC_SYSclk_DIV_22,
	ADC_SYSclk_DIV_24,
	ADC_SYSclk_DIV_26,
	ADC_SYSclk_DIV_28,
	ADC_SYSclk_DIV_30,
	ADC_SYSclk_DIV_32,
} ADC_SPEED_enum;


//此枚举定义不允许用户修改
typedef enum    // 枚举ADC通道
{
    ADC_12BIT=0,    //12位分辨率
	ADC_11BIT,		//11位分辨率
	ADC_10BIT,		//10位分辨率
	ADC_9BIT,    	//9位分辨率
	ADC_8BIT,     	//8位分辨率

}ADCRES_enum;

void adc_init(ADCN_enum adcn,ADC_SPEED_enum speed);
uint16 adc_once(ADCN_enum adcn,ADCRES_enum resolution);

u16 GetADCResult(u8 ch);   
#endif