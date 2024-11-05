#include "bsp_led.h"


/*初始化LED*/
void led_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);   //设置复用
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X10B0);  /*设置io电器属性*/


    /*GPIO初始化*/
    GPIO1->GDIR = 0x8;  //设置为输出
    GPIO1->DR &= ~(1 << 3); //打开led灯
}
void led_on(void)
{
     GPIO1->DR &= ~(1<<3); //打开led灯bit3清零
}
void led_off(void)
{
     GPIO1->DR |= (1<<3); //关闭led灯bit3至高
}
//led控制函数
void led_switch(int led,int status)
{

    switch(led)
    {
        case LED0:
            if(status == ON) 
                GPIO1->DR &= ~(1<<3); //打开led灯bit3清零
            else if(status == OFF)
                GPIO1->DR |= (1<<3); //关闭led灯bit3至高
            break;
    }
}