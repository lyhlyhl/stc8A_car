#include "uart.h"

extern int dat_set;
struct recstr_struct //���ܵ��ַ��ṹ��
{
    char *p_head;
    char *p_now;
    char recstr[20];
};
struct recstr_struct rec;
u8 c_variable[10] = "1234", c_data[10];
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
        spilt_str();       //ֱ�ӷָ��ַ����õ����
                           //        uart_putstr(c_variable); //���������ʾ��
                           //        uart_putchar(' ');
                           //        uart_putstr(c_data);
    }
    else
    {
        *rec.p_now = dat;
        rec.p_now++;
    }
}
void spilt_str() // �ָ��ַ���
{
    u8 i, Possem, j, c;

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
    c = str_cmp_fuck("1234", "5462", c_variable);
    uart_putstr("\r\n");
    if (c == 0) //��ʼʶ��
    {
        dat_set = 2;
    }
    else
    {
        uart_putchar(c); //Ҫ��дstrcmp����
    }
}

char str_cmp_fuck(u8 *s_a, u8 *s_b, u8 *s_c)
{
    int p, q, i, t = 0;
    p = strlen(s_a);
    q = strlen(s_b);
    uart_putstr("\r\n");
    uart_putstr(s_a);
    uart_putstr("\r\n");
    uart_putstr(s_b);
    uart_putstr("\r\n");
    uart_putstr(s_c);
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