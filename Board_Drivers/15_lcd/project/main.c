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
#include "stdio.h"
#include "bsp_lcd.h"
#include "bsp_lcdapi.h"

/* 背景颜色索引 */
unsigned int backcolor[10] = {
	LCD_BLUE, 		LCD_GREEN, 		LCD_RED, 	LCD_CYAN, 	LCD_YELLOW, 
	LCD_LIGHTBLUE, 	LCD_DARKBLUE, 	LCD_WHITE, 	LCD_BLACK, 	LCD_ORANGE

}; 

int main(void)
{
    unsigned char index = 0;
	unsigned char state = OFF;
    int_init();
    clk_enable();   //使能时钟
    imx6u_clkinit();
    delay_init();
    uart_init();
    filterkey_init();
    /*初始化LED与beep*/
    beep_init();
    led_init();
    lcd_init();
    tftlcd_dev.forecolor = LCD_RED;

    /*设置LED闪烁*/
    while(1){
        lcd_clear(backcolor[index]);
		delayms(1); 	  
		lcd_show_string(10, 40, 260, 32, 32,(char*)"ALPHA IMX6U"); 	
		lcd_show_string(10, 80, 240, 24, 24,(char*)"RGBLCD TEST");
		lcd_show_string(10, 110, 240, 16, 16,(char*)"ATOM@ALIENTEK");      					 
		lcd_show_string(10, 130, 240, 12, 12,(char*)"2019/8/14");	      					 
	    index++;
		if(index == 10)
			index = 0;      
		state = !state;
		led_switch(LED0,state);
		delayms(1000);

    }

    return 0;
}