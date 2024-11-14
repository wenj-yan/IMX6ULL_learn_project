#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "imx6ul.h"
#include "bsp_int.h"
#include "bsp_exit.h"
#include "bsp_epittimer.h"
#include "bsp_keyfilter.h"
#include "bsp_uart.h"

int main(void)
{
    unsigned char a = 0 ;
    int_init();
    clk_enable();   //使能时钟
    imx6u_clkinit();
    delay_init();
    uart_init();
    filterkey_init();
    /*初始化LED与beep*/
    beep_init();
    led_init();
    

    /*设置LED闪烁*/
    while(1){
        puts("请输入一个字符：");
        a = getc();
        puts("\r\n");
        puts("您输入的字符为：");
        putc(a);
        puts("\r\n");
    }

    return 0;
}