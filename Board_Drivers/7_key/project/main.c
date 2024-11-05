#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_led.h"
#include "bsp_key.h"

int main(void)
{
    int state =0;
    clk_enable();   //使能时钟
    /*初始化LED与beep*/
    beep_init();
    led_init();
    key_init();

    /*设置LED闪烁*/
    while(1){
        
        if(key_getvalue() == KEY0_VALUE)
        {
            state = !state;
        }
        led_switch(LED0,state);
    }

    return 0;
}