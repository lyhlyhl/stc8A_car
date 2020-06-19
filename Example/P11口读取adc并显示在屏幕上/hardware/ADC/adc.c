#include "adc.h"
#include "math.h"


u16 GetADCResult(u8 ch)         //�������в��� ����ϸ������
{   
    u16 Vo,adc_value;     
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
