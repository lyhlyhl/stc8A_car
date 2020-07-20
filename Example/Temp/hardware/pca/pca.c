#include "pca.h"
#include "common.h"

#include "SEEKFREE_TSL1401.h"

unsigned long length = 0;

uint16 ccp_value[4] = {0,0,0,0};
uint16 pca_time_ms[4] = {0,0,0,0};


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ�ʹ���û��������
//  @param      NULL            	
//  @return     void
//  Sample usage:               �����û����ã��û���ʹ��h�ļ��еĺ궨��
//-------------------------------------------------------------------------------------------------------------------
/*
void pca_init(PCAN_enum pca_n,PCAMODE_enum pca_mode)
{

	CCON = 0;
	CMOD = 0x03<<1;	//ECI �ŵ��ⲿ����ʱ��
	
	if(PCA_1 == pca_n)
	{
		switch(pca_mode)
		{
			case NONE:
			{
				CCAPM0 = 0x00;
				break;
			}
			case PWM_MODE_N0_ISR:
			{
				CCAPM0 = 0x42;
				break;
			}
			case PWM_MODE_RISING_EDGE_ISR:
			{
				CCAPM0 = 0x63;
				break;
			}
			case PWM_MODE_FALLING_EDGE_ISR:
			{
				CCAPM0 = 0x53;
				break;
			}
			
			case PWM_MODE_BOTH_EDGE_ISR:
			{
				CCAPM0 = 0x73;
				break;
			}
			case RISING_EDGE_CAPTURE:
			{
				CCAPM0 = 0x20;
				break;
			}
			case FALLING_EDGE_CAPTURE:
			{
				CCAPM0 = 0x10;
				break;
			}
			case BOTH_EDGE_CAPTURE:
			{
				CCAPM0 = 0x30;
				break;
			}
			case SOFT_TIMER:
			{
				CCAPM0 = 0x49;
				CR = 1;
				break;
			}		
			case HIGH_SPEED_PULSE_OUTPUT:
			{
				CCAPM0 = 0x4C;
				break;
			}
		}
	}
}



*/

u32 sys_clk = 22118400;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����жϳ�ʼ��
//  @param      pca_n       pcaͨ����
//  @param      time        �����ж�ʱ��(1ms-45ms)
//  @return     void
//  Sample usage:     		pca_init_interrupt_ms(PCA_0, 1); ��ʼ��1msһ���ж�
//-------------------------------------------------------------------------------------------------------------------
void pca_init_interrupt_ms(PCAN_enum pca_n,uint16 time_ms)
{
	uint16 cr_count;
	CR = 0;				// �ر� PCA ��ʱ��
	cr_count = (CH<<8) | CL;
	if(PCA_0 == pca_n)
	{
		time_ms = (sys_clk / (12 * (1000 / time_ms)));
		pca_time_ms[0] = time_ms;
		CCAPM0 = 0x49;
		CCAP0L = CL;
		CCAP0H = CH;
		ccp_value[0] = ccp_value[0] + pca_time_ms[0] + cr_count;
	}
	if(PCA_1 == pca_n)
	{
		time_ms = (sys_clk / (12 * (1000 / time_ms)));
		pca_time_ms[1] = time_ms;
		CCAPM1 = 0x49;
		CCAP1L = CL;
		CCAP1H = CH;
		ccp_value[1] = ccp_value[1] + pca_time_ms[1] + cr_count;
	}

	if(PCA_2 == pca_n)	
	{
		time_ms = (sys_clk/(12*(1000/time_ms)));
		pca_time_ms[2] = time_ms;
		CCAPM2 = 0x49;
		CCAP2L = CL;
		CCAP2H = CH;
		ccp_value[2] = ccp_value[2] + pca_time_ms[2] + cr_count;
	}
//	PCA_3������ʱ
//	if(PCA_3 == pca_n)	
//	{
//		time_ms = (sys_clk/(12*(1000/time_ms)));
//		pca_time_ms[3] = time_ms;
//		CCAPM3 = 0x49;
//		CCAP3L = ccp_value[3];
//		CCAP3H = ccp_value[3] >> 8;
//		ccp_value[3] += pca_time_ms[3];
//	}
	CR = 1;				// ���� PCA ��ʱ��
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      PCA���ؼ�����
//  @param      pca_n       pcaͨ����
//  @return     void
//  Sample usage:     		pca_init_interrupt_ms(PCA_0, 1); ��ʼ��1msһ���ж�
//-------------------------------------------------------------------------------------------------------------------
void pca_reload_counter(PCAN_enum pca_n)
{
	
	if(PCA_0 == pca_n)
	{
		//���ؼ�����
		CCAP0L = ccp_value[0];
		CCAP0H = ccp_value[0] >> 8;
		ccp_value[0] += pca_time_ms[0];
	}

	if(PCA_1 == pca_n)
	{
		//���ؼ�����
		CCAP1L = ccp_value[1];
		CCAP1H = ccp_value[1] >> 8;
		ccp_value[1] += pca_time_ms[1];
	}
	
	
	if(PCA_2 == pca_n)
	{
		//���ؼ�����
		CCAP2L = ccp_value[2];
		CCAP2H = ccp_value[2] >> 8;
		ccp_value[2] += pca_time_ms[2];
	}
	
	
	if(PCA_3 == pca_n)
	{
		//���ؼ�����
		CCAP3L = ccp_value[3];
		CCAP3H = ccp_value[3] >> 8;
		ccp_value[3] += pca_time_ms[3];
	}
}


//PCA���ڶ�ʱ���ж�
void PCA_Isr() interrupt 7
{
	if(PCA0_GET_FLAG)
	{
		//����жϱ�־λ
		PCA_CLEAR_FLAG(PCA_0);	

		//���ؼ�����
		pca_reload_counter(PCA_0);
		
		//����CCD�ɼ�����
		ccd_collect();
		//�ɼ���ɱ�־λ��1
		tsl1401_finish_flag = 1;
		
	}
	
	if(PCA1_GET_FLAG)
	{
		//����жϱ�־λ
		PCA_CLEAR_FLAG(PCA_1);	
		//���ؼ�����
		pca_reload_counter(PCA_1);
	}
	

	if(PCA2_GET_FLAG)
	{
		//����жϱ�־λ
		PCA_CLEAR_FLAG(PCA_2);	
		//���ؼ�����
		pca_reload_counter(PCA_2);
	}
	
//	PCA_3������ʱ
	if(PCA3_GET_FLAG)
	{
		//����жϱ�־λ
		PCA_CLEAR_FLAG(PCA_3);	
		
		//���ؼ�����
		pca_reload_counter(PCA_3);
	}
}

void pca_input_init(void)  //���벶���ʼ��
{
   CCON = 0x00;
   CMOD = 0x09;
   CL = 0x00;
   CH = 0x00;
   CCAPM0 = 0x10;
   CCAP0L = 0x00;
   CCAP0H = 0x00;
   CR = 1;
   EA = 1;
}
//			 
//void Pca_isr() interrupt 7
//{
//   static unsigned char cnt = 0;
//   static unsigned int count0 = 0;
//   static unsigned int count1 = 0;
//   if(CF)
//   {
//      CF = 0;
//      cnt++;
//   }
//   if(CCF0)
//   {
//      CCF0 = 0;
//      count0=count1;
//      count1 = CCAP0H<<8 | CCAP0L;
//      length = 0;
//      length = count1+65536*cnt;
//      CL = 0x00;
//      CH = 0x00;
//      cnt = 0;
//      
//      //LED = ~LED;
//   }
//}


