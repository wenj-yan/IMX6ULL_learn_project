## 按键输入实验

- IO接口：UART1_CTS

  按下：低电平

  松开：高电平

  方法：

  - 初始化IO引脚复用为GPIO，复用为 GPIO1_IO18
  - 设置IO电器属性
  - 初始化IO-输入模式
  - 读取电平

  **bss段代码必须四字节对齐，不然会出错**

  对 GPIO 的操作编写一个函数集合，也就是编写一个 GPIO 驱动文件，GPIO的驱动文件放到“gpio”文件夹里面。
