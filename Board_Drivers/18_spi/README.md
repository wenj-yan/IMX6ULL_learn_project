## SPI

I2C速度慢，最高只能到400khz。

SPI，SPI 全称是 Serial  Perripheral Interface，也就是串行外围设备接口。SPI 是 Motorola 公司推出的一种同步串行接口技术，是一种高速、全双工的同步通信总线，SPI 时钟频率相比 I2C 要高很多，最高可以工作在上百 MHz。

一般 SPI 需要 4 根线，但是也可以使用三根线(单向传输)。

- CS/SS，Slave Select/Chip Select，这个是片选信号线，用于选择需要进行通信的从设备。 I2C 主机是通过发送从机设备地址来选择需要进行通信的从机设备的，SPI 主机不需要发送从机设备，直接将相应的从机设备片选信号拉低即可。  
- SCK，Serial Clock，串行时钟，和 I2C 的 SCL 一样，为 SPI 通信提供时钟。  
- MOSI/SDO，Master Out Slave In/Serial Data Output，简称主出从入信号线，这根数据线 只能用于主机向从机发送数据，也就是主机输出，从机输入。  
- MISO/SDI，Master In Slave Out/Serial Data Input，简称主入从出信号线，这根数据线只能用户从机向主机发送数据，也就是主机输入，从机输出。 


**工作模式**

SPI 有四种工作模式，通过串行时钟极性(CPOL)和相位(CPHA)的搭配来得到四种工作模式：  

- CPOL=0，串行时钟空闲状态为低电平。  
- CPOL=1，串行时钟空闲状态为高电平，此时可以通过配置时钟相位(CPHA)来选择具体的传输协议。  
- CPHA=0，串行时钟的第一个跳变沿(上升沿或下降沿)采集数据。  
- CPHA=1，串行时钟的第二个跳变沿(上升沿或下降沿)采集数据。 


SPI 的时序图很简单，不像 I2C 那样还要分为读时序和写时序，因为 SPI 是全双工的，所以读写时序可以一起完成。

**ECSPI外设**

ECSPI 有 6432 个接收 FIFO(RXFIFO)和 6432 个发送 FIFO(TXFIFO)

①、全双工同步串行接口。

②、可配置的主/从模式。  

③、四个片选信号，支持多从机。  

④、发送和接收都有一个 32x64 的 FIFO。  

⑤、片选信号 SS/CS，时钟信号 SCLK 极性可配置。  

⑥、支持 DMA。 

I.MX6U 的 ECSPI 可以工作在主模式或从模式，本章我们使用主模式，I.MX6U **有 4 个 ECSPI，每个 ECSPI 支持四个片选信号**，也就说，如果你要使用 ECSPI 的硬件片选信号的话， 一个 ECSPI 可以支持 4 个外设。如果不使用硬件的片选信号就可以支持无数个外设，我们不使用硬件片选信号，因为硬件片选信号只能使用指定的片选 IO，**软件片选**的话可以使用任意的 IO。 

**重要寄存器**

- ECSPIx_CONREG：控制寄存器
- ECSPIx_CONFIGREG：配置寄存器
- ECSPIx_PERIODREG：采样周期寄存器
- ECSPIx_STATREG：状态寄存器
- ECSPIx_TXDATA 和 ECSPIx_RXDATA：数据寄存器