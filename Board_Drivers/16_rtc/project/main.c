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
#include "bsp_rtc.h"

/* 背景颜色索引 */
unsigned int backcolor[10] = {
	LCD_BLUE, 		LCD_GREEN, 		LCD_RED, 	LCD_CYAN, 	LCD_YELLOW, 
	LCD_LIGHTBLUE, 	LCD_DARKBLUE, 	LCD_WHITE, 	LCD_BLACK, 	LCD_ORANGE

}; 

int main(void)
{
    unsigned char key = 0;
	int i = 3, t = 0;
	char buf[160];
	struct rtc_datetime rtcdate;
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
    rtc_init(); 				/* 初始化RTC	 		*/


    tftlcd_dev.forecolor = LCD_RED;
	lcd_show_string(50, 10, 400, 24, 24, (char*)"ALPHA-IMX6UL RTC TEST");    /* 显示字符串 */
	lcd_show_string(50, 40, 200, 16, 16, (char*)"ATOM@ALIENTEK");  
	lcd_show_string(50, 60, 200, 16, 16, (char*)"2019/3/27");  
	tftlcd_dev.forecolor = LCD_BLUE;
	memset(buf, 0, sizeof(buf));


    /*设置LED闪烁*/
    while(1){
        if(t==100)	//1s时间到了
		{
			t=0;
			printf("will be running %d s......\r", i);
			
			lcd_fill(50, 90, 370, 110, tftlcd_dev.backcolor); /* 清屏 */
			sprintf(buf, "will be running %ds......", i);
			lcd_show_string(50, 90, 300, 16, 16, buf); 
			i--;
			if(i < 0)
				break;
		}
		key = key_getvalue();
		if(key == KEY0_VALUE)
		{
			rtcdate.year = 2018;
   			rtcdate.month = 1;
    		rtcdate.day = 15;
    		rtcdate.hour = 16;
    		rtcdate.minute = 23;
    		rtcdate.second = 0;
			rtc_setdatetime(&rtcdate); /* 初始化时间和日期 */
			printf("\r\n RTC Init finish\r\n");
			break;
		}
			
		delayms(10);
		t++;
    }
	tftlcd_dev.forecolor = LCD_RED;
	lcd_fill(50, 90, 370, 110, tftlcd_dev.backcolor); /* 清屏 */
	lcd_show_string(50, 90, 200, 16, 16, (char*)"Current Time:");  			/* 显示字符串 */
	tftlcd_dev.forecolor = LCD_BLUE;

	while(1)					
	{	
		rtc_getdatetime(&rtcdate);
		sprintf(buf,"%d/%d/%d %d:%d:%d\r\n",rtcdate.year, rtcdate.month, rtcdate.day, rtcdate.hour, rtcdate.minute, rtcdate.second);
		lcd_fill(50,110, 300,130, tftlcd_dev.backcolor);
		lcd_show_string(50, 110, 250, 16, 16,(char*)buf);  /* 显示字符串 */
		
		state = !state;
		led_switch(LED0,state);
		delayms(1000);	/* 延时一秒 */
	}
    return 0;
}