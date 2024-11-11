#include "bsp_delay.h"

/*短延时*/
void delay_short(volatile unsigned int n)
{
    while(n--){}

}
/*延时,大概1ms*/
void delay(volatile unsigned int n)
{
    while(n--){
        delay_short(0x7ff);
    }

}