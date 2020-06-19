#include "adc.h"
#include "math.h"


u16 GetADCResult(u8 ch)         //这里如有不懂 请仔细看资料
{   
    u16 Vo,adc_value;     
    P1M0=0x00;
    P1M1=0x01;
   //选择P1口的哪一口 这里的口和ch要对应才能达到选择该口
    ADC_CONTR = ADC_POWER | ADC_START | ch ;//启动adc电源，开始A/D转换 ，配置采集口
                                                         // 这么用语句的主要原因就是不能位寻址
                                                         //   通道选择在后3位所以直接用一个整数表示ch
                                                         //例如ch=6 那么对应的后三位就是110           
    _nop_();         //Must wait before inquiry ， 
    _nop_(); //设置ADC_CONTR寄存器后需加4个CPU时钟周期的延时，才能保证值被写入ADC_CONTR寄存器 
//    _nop_(); 
//    _nop_(); 
    while (!(ADC_CONTR & ADC_FLAG));//Wait complete flag 		等待转化完成
   ADC_CONTR &= ~ADC_FLAG;         //Close ADC 将标志位清零等待下次硬件置1
   //也可以写成 ADC_CONTR= ADC_CONTR & ( ~ADC_FLAG)
 
	//只读取8位ADC采集结果 并 以5v为基准进行换算
    //Vo=ADC_RES;//*25/256;                 //Return ADC result（为显示整数，这里将电压值扩大了十倍） 
                                         //5/256  因为是8位 把5V分成256份  ADC_RES为采集的份数
                                         //ADC_RES*（5/256） 为采集的电压值  然后扩大10倍便于计算
   
   ADCCFG=0x20;
   adc_value = ADC_RES;  //存储 ADC 的 10 位结果的高 2 位
	adc_value <<= 8;
	//adc_value = ADC_RESL; 
	adc_value |= ADC_RESL;  //存储 ADC 的 10 位结果的低 8 位
   //adc_value = adc_value*25;
    return adc_value;
} 
