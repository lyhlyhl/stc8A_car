#ifndef PCA_H
#define PCA_H

#include "common.h"


//���PCA��־λ
#define PCA_CLEAR_FLAG(x)	(CCON &= ~(1<<x))


//��ȡPCA�жϱ�־λ
#define PCA0_GET_FLAG		CCF0
#define PCA1_GET_FLAG		CCF1
#define PCA2_GET_FLAG		CCF2
#define PCA3_GET_FLAG		CCF3

//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��PCAͨ��
{
	PCA_0 = 0,
	PCA_1,
	PCA_2, 	
	PCA_3, 	//�ѱ���ʱռ��

}PCAN_enum;


//��ö�ٶ��岻�����û��޸�
//typedef enum    // ö��PCA ģʽ
//{
//	NONE,							//�޲���
//	PWM_MODE_N0_ISR,				//6/7/8/10 λ PWM ģʽ�����ж�
//	PWM_MODE_RISING_EDGE_ISR,		//6/7/8/10 λ PWM ģʽ�������������ж�
//	PWM_MODE_FALLING_EDGE_ISR,		//6/7/8/10 λ PWM ģʽ�������½����ж�
//	PWM_MODE_BOTH_EDGE_ISR,			//6/7/8/10 λ PWM ģʽ�����������ж�
//	RISING_EDGE_CAPTURE,			//16 λ�����ز���
//	FALLING_EDGE_CAPTURE,			//16 λ�½��ز���
//	BOTH_EDGE_CAPTURE,				//16 λ���ز���
//	SOFT_TIMER,						//16 λ�����ʱ��
//	HIGH_SPEED_PULSE_OUTPUT,		//16 Ϊ�����������
//}PCAMODE_enum;



extern u16 ccp_value[4];
extern u16 pca_time_ms[4];

void pca_init_interrupt_ms(PCAN_enum pca_n,uint16 time_ms);

//-------------------�����ж�----------------------//
void pca_reload_counter(PCAN_enum pca_n);



void pca_input_init(); 
#endif




