## BSP工程管理实验

目的：模块化整理代码，同一个属性的文件存放在同一个目录里面。

并且把对应驱动放到相应位置



指定头文件路径：创建.vscode，打开c++配置器，可以生成一个json文件,通过递归寻找所有文件夹，当然也可以自己设置。

```json
"includePath": [
                "${workspaceFolder}/**"
            ],
```

### 编写通用makefile

Makefile指定头文件路径，需要-I。我们编译源码的时候需要指定头文件路径。先来学习几个函数：

#### **1.patsubst：**模式字符串替换函数

#### 2.wildcard：让通配符在变量中展开

#### 3.foreach：循环查找函数

#### 4.VPATH关键字

如果没有指明这个变量， make 只会在当前的目录中去找寻依赖文件和目标文件。如果定义了这个变量，那么，make 就会在当当前目录找不到的情况下，到所指定的目录中去找寻文件了。

#### result

以下需要仔细认真学习：

```makefile
CROSS_COMPILE ?= arm-linux-gnueabihf-
TARGET		  ?= bsp

CC 		:= $(CROSS_COMPILE)gcc
LD		:= $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

INCDIRS   	:= 	imx6ul \
				bsp/clk \
				bsp/delay \
				bsp/led

SRCDIRS     := 	project \
				bsp/clk\
				bsp/delay \
				bsp/led

INCLUDE 	:=	$(patsubst %,-I %,$(INCDIRS))

SFILES		:= 	$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.S))
CFILES 		:= 	$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SFILENDIR := $(notdir $(SFILES))
CFILENDIR := $(notdir $(CFILES))

SOBJS := $(patsubst %, obj/%, $(SFILENDIR:.S=.o))
COBJS := $(patsubst %, obj/%, $(CFILENDIR:.c=.o))
OBJS := $(SOBJS) $(COBJS) 

VPATH := $(SRCDIRS) 

.PHONY: clean

$(TARGET).bin : $(OBJS) 
	$(LD) -Timx6ul.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(SOBJS) : obj/%.o : %.S 
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

$(COBJS) : obj/%.o : %.c 
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

clean: 
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin $(COBJS) $(SOBJS)
```

