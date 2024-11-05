#include "bsp_beep.h"

/*beep初始化*/
void beep_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);   //设置复用
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0X10B0);  /*设置io电器属性*/


    /*GPIO初始化*/
    GPIO5->GDIR  |= (1 << 1);  //设置为输出
    GPIO5->DR |= (1 << 1); //关闭beep


}

void beep_on(void)
{
     GPIO5->DR &= ~(1<<1); //打开beep bit3清零
}
void beep_off(void)
{
     GPIO5->DR |= (1<<1); //关闭beep bit3至高
}

void beep_switch(int status) 
{ 
    if(status == ON) 
        GPIO5->DR &= ~(1 << 1); /* 打开蜂鸣器 */ 
    else if(status == OFF) 
        GPIO5->DR |= (1 << 1); /* 关闭蜂鸣器 */ 
} 