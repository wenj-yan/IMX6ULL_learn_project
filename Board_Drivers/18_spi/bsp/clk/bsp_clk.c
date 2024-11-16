#include "bsp_clk.h"

/*使能外设时钟*/
void clk_enable(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;

}

/*初始化时钟源*/
void imx6u_clkinit(void)
{
    unsigned int reg = 0;
    //设置主频，初始化主频为528Mhz(系统bootrom为396MHz)
    if(((CCM->CCSR >> 2) & 0X1) == 0)  //当前时钟使用pll_main_clk，也就是pll1
    {
        //1.切换时钟源
        CCM->CCSR &= ~(1<<8); //切换时钟源，设置step_clk = osc_clk = 24 M
        CCM->CCSR |= (1<<2);//切换时钟源，设置pll1_sw_clk = step_clk=24Mhz
    }
    //2.设置PLL1=1056MHz
    CCM_ANALOG->PLL_ARM = (1<<13) |((88 << 0) & 0X7F );//设置DIV_SEL=88与使能输出
    //3.设置2分频
    CCM->CACRR = 1 ;//低三位为001
    //4.切换回时钟
    CCM->CCSR &= ~(1<< 2);//清零bit2，设置pll1_sw_clk = pll1_main_clk=528Mhz

    /*设置PLL2的四路PFD时钟,PFD= 528*18/PFD_FRAC*/
    reg = CCM_ANALOG->PFD_528;//读出来
    reg &= ~(0x3f3f3f3f);  //将4个的对应位置清零
    reg |= (32 << 24);                  //pfd3=297MHz
    reg |= (24 << 16);                  //pfd2=396MHz
    reg |= (16 << 8 );                  //pfd1=594MHz
    reg |= (27 << 0 );                  //pfd0=352MHz
    CCM_ANALOG->PFD_528 = reg;

    /*设置PLL3的四路PFD时钟,PFD= 480*18/PFD_FRAC*/
    reg = 0;
    reg = CCM_ANALOG->PFD_480;//读出来
    reg &= ~(0x3f3f3f3f);  //将4个的对应位置清零
    reg |= (19 << 24);                  //pfd3=454.7MHz
    reg |= (17 << 16);                  //pfd2=508.2MHz
    reg |= (16 << 8 );                  //pfd1=540MHz
    reg |= (12 << 0 );                  //pfd0=720MHz
    CCM_ANALOG->PFD_480 = reg;

    /*设置AHB_CLK_ROOT = 132MHZ*/
    CCM->CBCMR &= ~(3<<18); //清零
    CCM->CBCMR |= (1<<18);   //设置CBCMR寄存器的PRE_PERIPH_ CLK_SEL位为01，选择时钟源为PFD2==396MHZ
    CCM->CBCDR &= ~(1<<25);  //clean,设置CBCDR寄存器的PERIPH_CLK_ SEL为0，选择PLL2
    while(CCM->CDHIPR & (1<< 5));//等待握手完成
    //三分频bootroom已经设置好了，这里面有bug，可以不用改
    //CCM->CBCDR &= ~(7 << 10);//clean
    //CCM->CBCDR |= (2 << 10);//三分频
    //while(CCM->CDHIPR & (1 << 1)); //等待握手信号完成

    /*设置IPG_CLK_ROOT = 66MHZ*/
    CCM->CBCDR &= ~(3 << 8);//CLEAN
    CCM->CBCDR |= (1 << 8);
    /*设置PER_CLK_ROOT = 66MHZ*/
    CCM->CSCMR1 &= ~(1 << 6);
    CCM->CSCMR1 &= ~(0X3F << 0);//1分频
    
    //设置UART根时钟为80M
    CCM->CSCDR1 &= ~(1<<6);
    CCM->CSCDR1 &= ~0X3F;
}
