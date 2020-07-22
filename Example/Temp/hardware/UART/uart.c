#include "uart.h"

extern int dat_set;
extern int uflag;

struct recstr_struct //接受的字符结构体
{
    char *p_head;
    char *p_now;
    char recstr[20];
};
struct recstr_struct rec;
u8 c_variable[10] = "1234", c_data[10];
u8 datee[10] = "adc";
void rec_struct_init() //结构体初始化赋值
{
    rec.p_head = rec.recstr;
    rec.p_now = rec.recstr;
}

void uart_putchar(u8 dat) //发送一个字节
{
    SBUF = dat;
    while (!TI)
        ;
    TI = 0;
}

void uart_putstr(u8 *str) //发送一个字符串
{
    while (*str)
    {
        uart_putchar(*str++);
    }
}

void uart_get_data() //获取数据添加到字符串中
{
    u8 rec_dat;
    rec_dat = SBUF;
    uart_rec_data_add(rec_dat);
}
void uart_rec_data_add(u8 dat) //识别通信协议
{
    if (dat == '+') //第一位为加号
    {
        rec.p_now = rec.recstr; //把当前的字符串指针指向头指针
    }
    else if (dat == '*') //如果最后一位为星号
    {
        *rec.p_now = '\0'; //最后添加结束符
                           //        uart_putstr(rec.recstr);
        //spilt_str();       //直接分割字符串得到结果
                           //        uart_putstr(c_variable); //方便调试显示用
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

void spilt_str() // 分割字符串
{
    u8 i, Possem, j;
	
    for (i = 0; rec.recstr[i] != '\0'; i++) //识别字符串中间的冒号的位置
    {
        if (rec.recstr[i] == ':')
        {
            Possem = i;
            break;
        }
    }
    for (j = 0; j < Possem; j++) //分别赋值给俩个字符串
    {
        c_variable[j] = rec.recstr[j];
    }
    c_variable[j] = '\0';

    for (i = Possem + 1; i <= strlen(rec.recstr); i++)
    {
        c_data[i - Possem - 1] = rec.recstr[i];
    }
    c_data[i - Possem - 1] = '\0';
	
    if (str_cmp_fuck(c_variable, "adc")) //开始识别
    {
        dat_set = atoi(c_data);
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