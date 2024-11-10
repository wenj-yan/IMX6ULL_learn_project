#include "bsp_key.h"
#include "bsp_delay.h"
#include "gpio.h"

/*初始化按键*/
void key_init(void)
{
    gpio_pin_config_t Kconfig;
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18,0);   //设置复用为IO
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0XF080);  /*设置io电器属性*/

    /*GPIO初始化*/
    Kconfig.direction = kGPIO_DigitalInput;
    gpio_init(GPIO1, 18, &Kconfig); 


}
/*读取IO值
 *返回值：0：按下 1：未按下

*/
// int read_key(void)
// {
//     int ret = 0;
//     ret = gpio_pinread(GPIO1,18);
//     return ret;
// }

int key_getvalue(void)
{
    int ret = 0;
    static unsigned char release = 1; /*为1表示按键释放*/

    if((release == 1) && (gpio_pinread(GPIO1,18)== 0 ))     /*按下*/
    {
        delay(10);
        release = 0;
        if(gpio_pinread(GPIO1,18) == 0) /*如果延时10ms还是0则有效*/
        {
            ret = KEY0_VALUE;
        }
    }
    else if(gpio_pinread(GPIO1,18)== 1)/*未按下*/
    {
        ret = KEY_NONE;
        release = 1;
    }
    return ret;
}