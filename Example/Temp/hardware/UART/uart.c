#include "uart.h"

extern int dat_set;
struct recstr_struct //���ܵ��ַ��ṹ��
{
    char *p_head;
    char *p_now;
    char recstr[20];
};
struct recstr_struct rec;
char c_variable[10], c_data[10];
void rec_struct_init()  //�ṹ���ʼ����ֵ
{
    rec.p_head = rec.recstr;
    rec.p_now = rec.recstr;
}

void uart_putchar(u8 dat)  //����һ���ֽ�
{
    SBUF = dat;
    while (!TI)
        ;
    TI = 0;
}

void uart_putstr(u8 *str)  //����һ���ַ���
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
void uart_rec_data_add(u8 dat)   //ʶ��ͨ��Э��
{
    if (dat == '+')  //��һλΪ�Ӻ�
    {
        rec.p_now = rec.recstr;  //�ѵ�ǰ���ַ���ָ��ָ��ͷָ��
    }
    else if (dat == '*')   //������һλΪ�Ǻ�
    {
        *rec.p_now = '\0'; //�����ӽ�����
        //uart_putstr(rec.recstr);
       spilt_str();  //ֱ�ӷָ��ַ����õ����
       uart_putstr(c_variable);  //���������ʾ��
       uart_putchar(' ');
       uart_putstr(c_data);
      
    }
    else
    {
        *rec.p_now = dat;
        rec.p_now++;
    }
}
void spilt_str()   // �ָ��ַ���
{
    u8 i, Possem,j;
      u8 dat[10]="dat_set";
    for (i = 0; rec.recstr[i] != '\0'; i++)  //ʶ���ַ����м��ð�ŵ�λ��
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
        c_data[i -Possem - 1] = rec.recstr[i];
    }
    c_data[i-Possem - 1] = '\0';
    
    if(strcmp(c_variable,dat) == 0)//��ʼʶ��
    {
      dat_set = 2;
    }
    else
    {
      uart_putchar(strcmp(c_variable,"dat_set")); //Ҫ��дstrcmp����
    }
}
