**为什么要用汇编？**

因为其他公司（ST）已经帮你写好了，而这个要自己写，需要使用汇编出示一下外设。才能用c这些语言。

- 使用汇编初始SOC外设
- 使用汇编初始化DDR（这一步IMX6U不需要）
- 设置SP指针，一般指向DDR，内部ram比较小，设置好C语言运行环境。（入栈出栈）

### 一、汇编LED原理分析

#### **1.开发板硬件原理分析**

而LED0接了GPIO3

<u>在STM32中我们是怎么做的？</u>

- <u>1.使能GPIO时钟</u>
- <u>2.复用设置GPIO，将其用作GPIO功能</u>
- <u>3.配置GPIO，速度，电器属性等</u>
- <u>4.使用GPIO，输出高低电平。</u>

IMX6U初始化：

- 1.使能时钟，CCGR0-6这7个寄存器控制了所有外设时钟使能。为了简单，设置为0xFFFFFFFF，相当于使能所有外设时钟。

- 2.IO复用设置、寄存器IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03

作为普通GPIO将末尾设置为0101=5，复用为GPIO

- 3.配置电器属性，寄存器IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03
  - 包括**压摆率、速度、驱动能力、开漏、上下拉**等。

1.SRE，设置压摆率（IO 电平跳变所需要的时间）如果你当前所使用的 IO 做高速通信的话就可以使用高压摆率。

2.DSE:设置驱动能力。

3.SPEED，设置速度。

- 配置GPIO功能，设置输入输出。

DR设置数据与读取，GDIR设置方向。

设置GPIO1_GDIR bit3为1，输出模式

GPIO1_DR bit3为1（高电平）

#### **2.汇编基础**

对于 Cortex-A 芯片来讲，大部分芯片在上电以后 C 语言环境还没准备好，所以第一行程序肯定是汇编的，至于要写多少汇编程序，那就看你能在哪一步把 C 语言环境准备好。所谓的 C 语言环境就是保证 C 语言能够正常运行。C 语言中的函数调用涉及到**出栈入栈**，出栈入栈就要对堆栈进行操作，所谓的堆栈其实就是一段内存，这段内存比较特殊，由 SP 指针访问，SP 指 针指向栈顶。芯片一上电 SP 指针还没有初始化，所以 C 语言没法运行，对于有些芯片还需要 **初始化 DDR**，因为芯片本身没有 RAM，或者内部 RAM 不开放给用户使用，用户代码需要在 DDR 中运行，因此一开始要用汇编来初始化 DDR 控制器。后面学习 Uboot 和 Linux 内核的时候汇编是必须要会的。 

**GNU汇编语法**

如果大家使用过 STM32 的话就会知道 MDK 和 IAR 下的启动文件 startup_stm32f10x_hd.s 其中的汇编语法是有所不同的，将 MDK 下的汇编文件直接复制到 IAR 下去编译就会出错，因 为 MDK 和 IAR 的编译器不同，因此对于汇编的语法就有一些小区别。我们要编写的是 ARM 汇编，编译使用的 **GCC 交叉编译器**，所以我们的汇编代码要符合 GNU 语法。

GNU 汇编语法适用于所有的架构，并不是 ARM 独享的，GNU 汇编由一系列的语句组成， 每行一条语句，每条语句有三个可选部分，如下：

```nasm
label：instruction @ comment
```

汇编程序的默认入口标号是start，不过我们也可以在链接脚本中使用 ENTRY 来指明其它 的入口点，下面的代码就是使用_start 作为入口标号：

```
.global _start 
 
_start: 
 ldr r0, =0x12 @r0=0x12 
```

**cortex-A7汇编指令**

处理器内部数据传输：MOV,**MRS,MSR**

存储器访问指令：LDR,STR

压栈出栈：PUSH,POP

跳转指令：B(不回来),BX,BL(回来),BLX

#### 3.驱动编写

```
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
```

#### 4.编译与下载

1. 编译程序

- 将.c.s文件编译为.o  

  - arm-linux-gnueabihf-gcc **编译文件**

  - ```
    arm-linux-gnueabihf-gcc -g -c led.s -o led.o 
    ```

- 将.o文件链接为elf格式的可执行文件

  - 连接起始地址就是代码运行的起始地址。

  - 对于6ull来说，链接起始地址应该指向RAM（内部RAM与外部RAM-DDR）内部RAM0x900000-0x91ffff，也可以放到外部DDR中，对于不同开发板放的地方不一样。统一用外部8780000。

  - 这里我们要区分“存储地址”和“运行地址”这两个概念，“存储地址”就是可执行文件存储在哪里，可执行文件的存储地址可以随意选择。“运行地址”就是代码运行的时候所处的地址，这个我们在链接的时候就已经确定好了，代码要运行，那就必须处于运行地址处，否则代码肯定运行出错。比如 I.MX6U 支持 SD 卡、EMMC、NAND 启动，因此代码可以存储到 SD 卡、EMMC 或者 NAND 中，但是要运行的话就必须将代码从 SD 卡、EMMC 或者 NAND 中拷贝到其运行地址(链接地址)处

  - arm-linux-gnueabihf-ld **链接文件** 

  - ```
    arm-linux-gnueabihf-ld -Ttext 0X87800000 led.o -o led.elf
    ```

- 将elf文件转化为bin文件

  - arm-linux-gnueabihf-objcopy **格式转换**

  - ```
    arm-linux-gnueabihf-objcopy -O binary -S -g led.elf led.bin
    ```

- 将elf文件反汇编-分析代码

  - arm-linux-gnueabihf-objdump **反汇编**

  - ```
    arm-linux-gnueabihf-objdump -D led.elf > led.dis
    ```

2.烧写代码

stm32烧写到内部flash

6ull支持sd卡、emmc、nand、nor、spi FLASH