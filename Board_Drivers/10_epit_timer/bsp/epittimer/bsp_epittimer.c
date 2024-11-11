#include "bsp_epittimer.h"
#include "bsp_int.h"
#include "bsp_led.h"
/* 
 * @description : 初始化 EPIT 定时器. 
 * EPIT 定时器是 32 位向下计数器,时钟源使用 ipg=66Mhz 
 * @param – frac : 分频值，范围为 0~4095，分别对应 1~4096 分频。 
 * @param - value : 倒计数值。 
 * @return : 无 
 */
void epit1_init(unsigned int frac,unsigned int value)
{
    if(frac > 0xFFF)  /*判断范围*/
    {
        frac = 0XFFF;
    }
    EPIT1->CR = 0 ;   /*清零CR寄存器*/
/* 
 * CR 寄存器: 
 * bit25:24 01 时钟源选择 Peripheral clock=66MHz 
 * bit15:4 frac 分频值 
 * bit3: 1 当计数器到 0 的话从 LR 重新加载数值 
 * bit2: 1 比较中断使能 
 * bit1: 1 初始计数值来源于 LR 寄存器值 
 * bit0: 0 先关闭 EPIT1 
 */ 
    EPIT1->CR = (1<<24 | frac << 4 | 1<<3 | 1<<2 | 1<<1); 
    EPIT1->LR = value; /* 加载寄存器值 (相当于倒计数值)*/ 
    EPIT1->CMPR = 0; /* 比较寄存器值 */ 

   /* 使能 GIC 中对应的中断 */ 
    GIC_EnableIRQ(EPIT1_IRQn); 
   /* 注册中断服务函数 */ 
    system_register_irqhandler(EPIT1_IRQn, (system_irq_handler_t)epit1_irqhandler, NULL); 
    
    EPIT1->CR |= 1<<0; /* 使能 EPIT1 */ 
}
void epit1_irqhandler(void) 
{ 
    static unsigned char state = 0; 
    state = !state; 
    if(EPIT1->SR & (1<<0)) /* 判断比较事件发生 */ 
    { 
        led_switch(LED0, state); /* 定时器周期到，反转 LED */ 
    } 
    EPIT1->SR |= 1<<0; /* 清除中断标志位 */ 
}