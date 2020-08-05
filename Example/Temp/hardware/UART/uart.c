#include "uart.h"

extern int uflag;
extern struct P_pid pid_angle,pid_speed,pid_turn;
extern float set_angle;
int flag_stop = 1;
extern int set_speed;
struct recstr_struct //���ܵ��ַ��ṹ��
{
    char *p_head;
    char *p_now;
    char recstr[20];
};
struct recstr_struct rec;
u8 c_variable[20] = "1234", c_data[10];
u8 datee[10] = "adc";
void rec_struct_init() //�ṹ���ʼ����ֵ
{
    rec.p_head = rec.recstr;
    rec.p_now = rec.recstr;
}

void uart_putchar(u8 dat) //����һ���ֽ�
{
    SBUF = dat;
    while (!TI)
        ;
    TI = 0;
}

void uart_putstr(u8 *str) //����һ���ַ���
{
    while (*str)
    {
        uart_putchar(*str++);
    }
}

void uart_get_data() //��ȡ������ӵ��ַ�����
{
    u8 rec_dat;
    rec_dat = SBUF;
	
    uart_rec_data_add(rec_dat);
}
void uart_rec_data_add(u8 dat) //ʶ��ͨ��Э��
{
    if (dat == '+') //��һλΪ�Ӻ�
    {
        rec.p_now = rec.recstr; //�ѵ�ǰ���ַ���ָ��ָ��ͷָ��
    }
    else if (dat == '*') //������һλΪ�Ǻ�
    {
        *rec.p_now = '\0'; //�����ӽ�����
                           //        uart_putstr(rec.recstr);
        //spilt_str();       //ֱ�ӷָ��ַ����õ����
                           //        uart_putstr(c_variable); //���������ʾ��
                           //        uart_putchar(' ');
                           //        uart_putstr(c_data);
			uflag = 1;
    }
    else
    {
        *rec.p_now = dat;
        rec.p_now++;
    }
}

void spilt_str() // �ָ��ַ���
{
    u8 i, Possem, j;
		char test[20];
	
    for (i = 0; rec.recstr[i] != '\0'; i++) //ʶ���ַ����м��ð�ŵ�λ��
    {
        if (rec.recstr[i] == ':')
        {
            Possem = i;
            break;
        }
    }
    for (j = 0; j < Possem; j++) //�ֱ�ֵ�������ַ���
    {
        c_variable[j] = rec.recstr[j];
    }
    c_variable[j] = '\0';

    for (i = Possem + 1; i <= strlen(rec.recstr); i++)
    {
        c_data[i - Possem - 1] = rec.recstr[i];
    }
    c_data[i - Possem - 1] = '\0';
	
//    if (str_cmp_fuck(c_variable, "adc")==0) //��ʼʶ��
//    {
//        dat_set = atof(c_data);
//			uart_putstr(rec.recstr);
//    }
		 if (str_cmp_fuck(c_variable, "fstop")==0) //��ʼʶ��
    {
      flag_stop= atof(c_data);
		  sprintf(test,"%.2f ok!\r\n",flag_stop);
			uart_putstr(test);
    }
		
		if (str_cmp_fuck(c_variable, "speed")==0) //��ʼʶ��
    {
      set_speed= atoi(c_data);
		  sprintf(test,"%d ok!\r\n",set_speed);
			uart_putstr(test);
    }
		
		if(str_cmp_fuck(c_variable, "Flag_Left")==0)
		{
			Flag_Left =atof(c_data);
			sprintf(test,"%d ok!\r\n",Flag_Left);
			uart_putstr(test);
		}
		if(str_cmp_fuck(c_variable, "Flag_Right")==0)
		{
			Flag_Right =atof(c_data);
			sprintf(test,"%d ok!\r\n",Flag_Right);
			uart_putstr(test);
		}	
		
		if(str_cmp_fuck(c_variable, "angle.Kp")==0)
		{
			pid_angle.Kp =atof(c_data);
			sprintf(test,"%.2f ok!\r\n",pid_angle.Kp);
			uart_putstr(test);
		}
			if(str_cmp_fuck(c_variable, "zhongzhi")==0)
		{
			set_angle=atof(c_data);
			sprintf(test,"%.2f ok!\r\n",set_angle);
			uart_putstr(test);
		}
		if(str_cmp_fuck(c_variable, "angle.Ki")==0)
		{
			pid_angle.Ki =atof(c_data);
			sprintf(test,"%.2f ok!\r\n",pid_angle.Ki);
			uart_putstr(test);
		}
		if(str_cmp_fuck(c_variable, "angle.Kd")==0)
		{
			pid_angle.Kd =atof(c_data);
			sprintf(test,"%.2f ok!\r\n",pid_angle.Kd);
			uart_putstr(test);
		}	
		
		if(str_cmp_fuck(c_variable, "speed.Kp")==0)
		{
			pid_speed.Kp =atof(c_data);
			sprintf(test,"%.2f ok!\r\n",pid_speed.Kp);
			uart_putstr(test);
		}	
		if(str_cmp_fuck(c_variable, "speed.Ki")==0)
		{
			pid_speed.Ki =atof(c_data);
			sprintf(test,"%.2f ok!\r\n",pid_speed.Ki);
			uart_putstr(test);
		}	
				
		if(str_cmp_fuck(c_variable, "turn")==0)
		{
			Turn[0][0] =atoi(c_data);
			sprintf(test,"%.2f ok!\r\n",Turn[0][0]);
			uart_putstr(test);
		}	
		if(str_cmp_fuck(c_variable, "turn1kd")==0)
		{
			Turn[0][1] =atoi(c_data);
			sprintf(test,"%.2f ok!\r\n",Turn[0][1]);
			uart_putstr(test);
		}	
		if(str_cmp_fuck(c_variable, "turn2kp")==0)
		{
			Turn[1][0] =atoi(c_data);
			sprintf(test,"%.2f ok!\r\n",Turn[1][0]);
			uart_putstr(test);
		}
		if(str_cmp_fuck(c_variable, "turn2kd")==0)
		{
			Turn[1][1] =atoi(c_data);
			sprintf(test,"%.2f ok!\r\n",Turn[1][1]);
			uart_putstr(test);
		}
		
}

char str_cmp_fuck(u8 *s_a, u8 *s_b)
{
    int p, q, i, t = 0;
    p = strlen(s_a);
    q = strlen(s_b);

    for (i = 0; s_a[i] != '\0' && s_b[i] != '\0'; i++)
    {
        if (s_a[i] > s_b[i])
        {
            t = 1;
            return t;
        }
        if (s_a[i] < s_b[i])
        {
            t = -1;
            return t;
        }
    }
    if (t == 0)
    {
        if (p > q)
            t = 1;
        if (p < q)
            t = -1;
    }
    return t;
}