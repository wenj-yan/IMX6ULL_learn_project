自己编写这些寄存器定义不仅费时费力，没有任何意义，而且很容易写错，幸好 NXP 官方为 I.MX6ULL 编写了 SDK 包，在 **SDK 包里面 NXP 已经编写好了寄存器定义文件， 所以我们可以直接移植 SDK 包里面的文件来用**。方便我们的开发。

重点是需要 SDK 包里面与寄存器定义相关的文件，一共需要如下三个文件：  **fsl_common.h：位置为 SDK_2.2_MCIM6ULL\devices\MCIMX6Y2\drivers\fsl_common.h。  fsl_iomuxc.h: 位置为 SDK_2.2_MCIM6ULL\devices\MCIMX6Y2\drivers\fsl_iomuxc.h。  MCIMX6Y2.h: 位置为 SDK_2.2_MCIM6ULL\devices\MCIMX6Y2\MCIMX6YH2.h。**  

整个 SDK 包我们就需要上面这三个文件，把这三个文件准备好，我们后面移植要用。

这三个文件直接编译的话肯定会出错的！需要对其做删减。

SDK包里面会用到很多数据类型，所以我们需要定义很多数据类型。

新建一个名为 cc.h 的头文件，cc.h 里面存放一些 SDK 库文件需要使用到的数据类型。

使用函数：

```c
IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0); 
IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0X10B0); 
```

定义：

```c
//设置引脚复用
static inline void IOMUXC_SetPinMux(uint32_t muxRegister,
                                    uint32_t muxMode,
                                    uint32_t inputRegister,
                                    uint32_t inputDaisy,
                                    uint32_t configRegister,
                                    uint32_t inputOnfield)
{
    *((volatile uint32_t *)muxRegister) =
        IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(muxMode) | IOMUXC_SW_MUX_CTL_PAD_SION(inputOnfield);

    if (inputRegister)
    {
        *((volatile uint32_t *)inputRegister) = IOMUXC_SELECT_INPUT_DAISY(inputDaisy);
    }
}
//设置电器属性
static inline void IOMUXC_SetPinConfig(uint32_t muxRegister,
                                       uint32_t muxMode,
                                       uint32_t inputRegister,
                                       uint32_t inputDaisy,
                                       uint32_t configRegister,
                                       uint32_t configValue)
{
    if (configRegister)
    {
        *((volatile uint32_t *)configRegister) = configValue;
    }
}
```

