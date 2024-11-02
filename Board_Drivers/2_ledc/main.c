#include "main.h"

/*使能外设时钟*/
void clk_enable(void)
{
    CCM_CCGR0 = 0xFFFFFFFF;
    CCM_CCGR1 = 0xFFFFFFFF;
    CCM_CCGR2 = 0xFFFFFFFF;
    CCM_CCGR3 = 0xFFFFFFFF;
    CCM_CCGR4 = 0xFFFFFFFF;
    CCM_CCGR5 = 0xFFFFFFFF;
    CCM_CCGR6 = 0xFFFFFFFF;

}

/*初始化LED*/
void led_init(void)
{
    SW_MUX_GPIO1_IO03 = 0X5;   //设置复用
    SW_PAD_GPIO1_IO03 = 0X10B0;  /*设置io电器属性*/

    /*GPIO初始化*/
    GPIO1_GDIR = 0X8 ; //设置为输出
    GPIO1_DR = 0X0; //打开led灯
}

/*短延时*/
void delay_short(volatile unsigned int n)
{
    while(n--){}

}
/*延时,大概1ms*/
void delay(volatile unsigned int n)
{
    while(n--){
        delay_short(0x7ff);
    }

}


void led_on(void)
{
    GPIO1_DR &= ~(1<<3); //打开led灯bit3清零
}
void led_off(void)
{
    GPIO1_DR |= (1<<3); //关闭led灯bit3至高
}
int main(void)
{
    clk_enable();   //使能时钟
    /*初始化LED*/
    led_init();



    /*设置LED闪烁*/
    while(1){
        led_on();
        delay(500);
        led_off();
        delay(500);
    }

    return 0;
}