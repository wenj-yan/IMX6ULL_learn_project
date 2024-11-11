#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "imx6ul.h"
#include "bsp_int.h"
#include "bsp_exit.h"
#include "bsp_epittimer.h"

int main(void)
{
    int_init();
    clk_enable();   //使能时钟
    /*初始化LED与beep*/
    beep_init();
    led_init();
    key_init();
    imx6u_clkinit();
    exit_init();
    epit1_init(0,66000000/2);   //500ms定时

    /*设置LED闪烁*/
    while(1){
        
        delay(500);
    }

    return 0;
}