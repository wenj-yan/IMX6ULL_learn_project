## 定时器消抖实验

中断嵌套：中断中开启定时器中断。

步骤如下：  

1、**配置按键 IO 中断**  配置按键所使用的 IO，因为要使用到中断驱动按键，所以要配置 IO 的中断模式。  

2、**初始化消抖用的定时器**  上面已经讲的很清楚了，消抖要用定时器来完成，所以需要初始化一个定时器，这里使用 上一章讲解的 EPIT1 定时器，也算是对 EPIT1 定时器的一次巩固。定时器的定时周期为 10ms， 也可根据实际情况调整定时周期。  

3、**编写中断处理函数**  需要编写两个中断处理函数：按键对应的 GPIO 中断处理函数和 EPIT1 定时器的中断处理函数。在按键的中断处理函数中主要用于开启 EPIT1 定时器，EPIT1 的中断处理函数才是重点， 按键要做的具体任务都是在定时器 EPIT1 的中断处理函数中完成的，比如控制蜂鸣器打开或关闭。
