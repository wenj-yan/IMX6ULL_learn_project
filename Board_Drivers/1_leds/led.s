.global _start   @全局标号

_start:
    /*使能所有外设时钟 */
    ldr r0, =0x020c4068 @CCGR0
    ldr r1, =0xffffffff @写入的数据
    str r1, [r0] @写入

    ldr r0, =0x020c406c @CCGR1
    str r1, [r0] @写入

    ldr r0, =0x020c4070 @CCGR2
    str r1, [r0] @写入

    ldr r0, =0x020c4074 @CCGR3
    str r1, [r0] @写入

    ldr r0, =0x020c4078 @CCGR4
    str r1, [r0] @写入

    ldr r0, =0x020c407c @CCGR5
    str r1, [r0] @写入

    ldr r0, =0x020c4080 @CCGR6
    str r1, [r0] @写入

    /*配置IO复用 
     *IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 = 5
     *地址为0x020e0068
    */
    ldr r0, =0x020e0068 @IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03
    ldr r1, =0x5 @写入的数据5
    str r1, [r0] @写入

    /*配置GPIO1_IO03电气属性
     *寄存器：IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03
     *地址：20E_02F4h
     *bit0:0 低速率
     *bit5:3:  110  R0/6驱动能力
     *bit7:6:  10   100mhz速度
     *bit11： 0     关闭开漏输出
     *bit12： 1     使能pull
     *bit13： 0     keeper
     *bit15:14: 00  100k下拉电阻
     *bit16:  0     关闭HYS   
     */
    ldr r0, =0x020e02f4 @IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03
    ldr r1, =0x10b0 @写入的数据
    str r1, [r0] @写入

    /*设置GPIO功能 
     *寄存器：GPIO1_GDIR，设置为输出
     *地址：209_C004
    */
    ldr r0, =0x0209c004 @GPIO1_GDIR
    ldr r1, =0x8 @写入的数据
    str r1, [r0] @写入

    /*打开LED 设置GPIO1_IO03为0 
     *地址：209_C000
     *寄存器：GPIO1_DR
    */
    ldr r0, =0x0209c000 @GPIO1_DR
    ldr r1, =0x0 @写入的数据
    str r1, [r0] @写入


loop:
    b loop
    