#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"

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