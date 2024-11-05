CROSS_COMPILE ?= arm-linux-gnueabihf-
Name		  ?= ledc

CC 		:= $(CROSS_COMPILE)gcc
LD		:= $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

OBJS 	:= start.o main.o

$(Name).bin:$(OBJS)
	$(LD) -Timx6ul.lds -o $(Name).elf $^
	$(OBJCOPY) -O binary -S $(Name).elf $@
	$(OBJDUMP) -D -m arm $(Name).elf > $(Name).dis

%.o:%.s
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<
	
%.o:%.S
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<
	
%.o:%.c
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<
	
clean:
	rm -rf *.o $(Name).bin $(Name).elf $(Name).dis