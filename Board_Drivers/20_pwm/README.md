## 背光调节

可以通过调高背光来看清屏幕，在光线比较暗的地方可以调低 背光，防止伤眼睛并且省电。

**PWM外设**

I.MX6U 一共有 8 路 PWM 信号，每个 PWM 包含一个 16 位的计数器和一个 4 x 16 的数据 FIFO。

在一个周期内，PWM 从 0X0000 开始计数的时候，PWM 引脚先输出高电平(默认情况下， 可以通过配置输出低电平)。采样 FIFO 中保存的采样值会在每个时钟和计数器值进行比较，当 采样值和计数器相等的话 PWM 引脚就会改为输出低电平(默认情况下，同样可以通过配置输出 高电平)。计数器会持续计数，直到和周期寄存器 PWMx_PWMPR(x=1~8) + 1 的值相等，这样一个周期就完成了。所以，采样 FIFO 控制着占空比，而采样 FIFO 里面的值来源于采样寄存器 PWMx_PWMSAR，因此相当于 PWMx_PWMSAR 控制着占空比。

**配置步骤**

1、配置引脚 GPIO1_IO8 ：配置 GPIO1_IO08 的复用功能，将其复用为 PWM1_OUT 信号线。  

2、初始化 PWM1  ：初始化 PWM1，配置所需的 PWM 信号的频率和默认占空比。  

3、设置中断  ：因为 FIFO 中的采样值每个周期都会少一个，所以需要不断的向 FIFO 中写入采样值，防止其为空。我们可以使能 FIFO 空中断，这样当 FIFO 为空的时候就会触发相应的中断，然后在中断处理函数中向 FIFO 写入采样值。  

4、使能 PWM1  ：配置好 PWM1 以后就可以开启了。