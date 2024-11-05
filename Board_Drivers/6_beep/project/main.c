#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_led.h"

int main(void)
{
    clk_enable();   //使能时钟
    /*初始化LED与beep*/
    beep_init();
    led_init();

    /*设置LED闪烁*/
    while(1){
        led_switch(LED0,ON);
        beep_switch(ON);
        delay(1000);
        led_switch(LED0,OFF);
        beep_switch(OFF);
        delay(1000);


    }

    return 0;
}