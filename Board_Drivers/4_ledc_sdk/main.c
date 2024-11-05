#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

/*使能外设时钟*/
void clk_enable(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;

}

/*初始化LED*/
void led_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);   //设置复用
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X10B0);  /*设置io电器属性*/


    /*GPIO初始化*/
    GPIO1->GDIR = 0x8;  //设置为输出
    GPIO1->DR &= ~(1 << 3); //打开led灯
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
     GPIO1->DR &= ~(1<<3); //打开led灯bit3清零
}
void led_off(void)
{
     GPIO1->DR |= (1<<3); //关闭led灯bit3至高
}
int main(void)
{
    clk_enable();   //使能时钟
    /*初始化LED*/
    led_init();



    /*设置LED闪烁*/
    while(1){
        led_on();
        delay(1000);
        led_off();
        delay(1000);
    }

    return 0;
}