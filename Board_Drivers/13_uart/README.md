## UART串口实验

Universal Asynchronous Receiver/Transmitter（通用异步收发器）


我们只使用基础收发功能。

- 寄存器UARTx_URXD，保存串口接收到的数据
- 寄存器UARTx_UTXD，发送数据寄存器
- UARTx_UCRx，串口控制寄存器
- UARTx_UFCR，控制分频值，触发电平，模式选择。
- CCM_CSCDR，时钟源选择为内部时钟。（六分频为80M）
- UART_UFCR\UBIR\UBMR，决定波特率
- UARTx_USR1，状态寄存器。是否有数据读取等。