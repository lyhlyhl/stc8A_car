#include "adc.h"



u16 GetADCResult(u8 ch)         //�������в��� ����ϸ������
{   
    u16 adc_value;     
    P1M0=0x00;
    P1M1=0x01;
   //ѡ��P1�ڵ���һ�� ����Ŀں�chҪ��Ӧ���ܴﵽѡ��ÿ�
    ADC_CONTR = ADC_POWER | ADC_START | ch ;//����adc��Դ����ʼA/Dת�� �����òɼ���
                                                         // ��ô��������Ҫԭ����ǲ���λѰַ
                                                         //   ͨ��ѡ���ں�3λ����ֱ����һ��������ʾch
                                                         //����ch=6 ��ô��Ӧ�ĺ���λ����110           
    _nop_();         //Must wait before inquiry �� 
    _nop_(); //����ADC_CONTR�Ĵ��������4��CPUʱ�����ڵ���ʱ�����ܱ�ֵ֤��д��ADC_CONTR�Ĵ��� 
//    _nop_(); 
//    _nop_(); 
    while (!(ADC_CONTR & ADC_FLAG));//Wait complete flag 		�ȴ�ת�����
   ADC_CONTR &= ~ADC_FLAG;         //Close ADC ����־λ����ȴ��´�Ӳ����1
   //Ҳ����д�� ADC_CONTR= ADC_CONTR & ( ~ADC_FLAG)
 
	//ֻ��ȡ8λADC�ɼ���� �� ��5vΪ��׼���л���
    //Vo=ADC_RES;//*25/256;                 //Return ADC result��Ϊ��ʾ���������ｫ��ѹֵ������ʮ���� 
                                         //5/256  ��Ϊ��8λ ��5V�ֳ�256��  ADC_RESΪ�ɼ��ķ���
                                         //ADC_RES*��5/256�� Ϊ�ɼ��ĵ�ѹֵ  Ȼ������10�����ڼ���
   
   ADCCFG=0x20;
   adc_value = ADC_RES;  //�洢 ADC �� 10 λ����ĸ� 2 λ
	adc_value <<= 8;
	//adc_value = ADC_RESL; 
	adc_value |= ADC_RESL;  //�洢 ADC �� 10 λ����ĵ� 8 λ
   //adc_value = adc_value*25;
    return adc_value;
} 


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC��ʼ��
//  @param      adcn            ѡ��ADCͨ��
//  @param      speed      		ADCʱ��Ƶ��
//  @return     void
//  Sample usage:               adc_init(ADC_P10,ADC_SYSclk_DIV_2);//��ʼ��P1.0ΪADC����,ADCʱ��Ƶ�ʣ�SYSclk/2
//-------------------------------------------------------------------------------------------------------------------
void adc_init(ADCN_enum adcn,ADC_SPEED_enum speed)
{
	ADC_CONTR |= 1<<7;			//�� ADC ��Դ
	
	if((adcn >> 3) == 1) 		//P0��
	{
		//IO������Ϊ��������
		P0M0 &= ~(1 << (adcn & 0x07));
		P0M1 |= (1 << (adcn & 0x07));
	}
	else if((adcn >> 3) == 0) 	//P1��
	{
		//IO������Ϊ��������
		P1M0 &= ~(1 << (adcn & 0x07));
	    P1M1 |= (1 << (adcn & 0x07));
	}

	ADCCFG |= speed&0x0F;		//ADCʱ��Ƶ��SYSclk/2/16/speed&0x0F;

	ADCCFG |= 1<<5;		//ת������Ҷ��롣 ADC_RES �������ĸ� 2 λ�� ADC_RESL �������ĵ� 8 λ��
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADCת��һ��
//  @param      adcn            ѡ��ADCͨ��
//  @param      resolution      �ֱ���
//  @return     void
//  Sample usage:               adc_convert(ADC_P10, ADC_10BIT);
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_once(ADCN_enum adcn,ADCRES_enum resolution)
{
	uint16 adc_value;
	
	ADC_CONTR &= (0xF0);	//���ADC_CHS[3:0] �� ADC ģ��ͨ��ѡ��λ
	ADC_CONTR |= adcn;
	
	ADC_CONTR |= 0x40;  // ���� AD ת��
//	_nop_();
//	_nop_();
	while (!(ADC_CONTR & 0x20));  // ��ѯ ADC ��ɱ�־
	ADC_CONTR &= ~0x20;  // ����ɱ�־
	
	
	adc_value = ADC_RES;  //�洢 ADC �� 10 λ����ĸ� 2 λ
	adc_value <<= 8;
	adc_value |= ADC_RESL;  //�洢 ADC �� 10 λ����ĵ� 8 λ
	
	adc_value >>= resolution;//ȡ����λ
	

	return adc_value;
}
