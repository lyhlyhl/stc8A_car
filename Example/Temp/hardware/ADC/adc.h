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




//��ö�ٶ��岻�����û��޸�
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


//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��ADCͨ��
{
    ADC_12BIT=0,    //12λ�ֱ���
	ADC_11BIT,		//11λ�ֱ���
	ADC_10BIT,		//10λ�ֱ���
	ADC_9BIT,    	//9λ�ֱ���
	ADC_8BIT,     	//8λ�ֱ���

}ADCRES_enum;

void adc_init(ADCN_enum adcn,ADC_SPEED_enum speed);
uint16 adc_once(ADCN_enum adcn,ADCRES_enum resolution);

u16 GetADCResult(u8 ch);   
#endif