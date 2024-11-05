## 蜂鸣器实验

BEEP为低电平，蜂鸣器会叫。反之。

IO：SNVS_TAMPER1

方法与led实验相同：

- 初始化IO引脚复用为GPIO，复用为 GPIO5_IO01
- 设置IO电器属性
- 初始化IO
- 控制电平
