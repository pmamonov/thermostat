PREFIX=/home/piton/devel/arm/arm-2012.09/bin/arm-none-eabi
AS      = $(PREFIX)-as
CC      = $(PREFIX)-gcc
LD      = $(PREFIX)-ld
OBJCOPY = $(PREFIX)-objcopy

LDSCRIPT = stm32f102r8_flash.ld

CFLAGS = -mcpu=cortex-m3 -mthumb -Os -g\
 -I./inc\
 -ICM3/DeviceSupport/ST/STM32F10x\
 -ICM3/CoreSupport\
 -ISTM32_USB-FS-Device_Driver/inc\
 -ISTM32F10x_StdPeriph_Driver/inc\
 -DSTM32F10X_MD\
 -DUSE_STM3210B_EVAL\
 -DUSE_STDPERIPH_DRIVER

OBJ = src/startup_stm32f10x_md.o\
  src/main.o \
  src/hw_config.o\
  src/stm32_it.o\
  src/system_stm32f10x.o\
  src/usb_desc.o\
  src/usb_endp.o\
  src/usb_istr.o\
  src/usb_prop.o\
  src/usb_pwr.o\
  STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.o\
  STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.o\
  STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.o\
  STM32F10x_StdPeriph_Driver/src/misc.o\
  STM32_USB-FS-Device_Driver/src/usb_regs.o\
  STM32_USB-FS-Device_Driver/src/usb_int.o\
  STM32_USB-FS-Device_Driver/src/usb_mem.o\
  STM32_USB-FS-Device_Driver/src/usb_init.o\
  STM32_USB-FS-Device_Driver/src/usb_core.o\
  STM32_USB-FS-Device_Driver/src/usb_sil.o\
  CM3/CoreSupport/core_cm3.o\
  src/stm3210b_eval-strip.o

# CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.o\

all: main.bin

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@
	$(PREFIX)-size $<

main.elf: $(OBJ)
	$(CC) -o $@ -nostartfiles -Wl,-T$(LDSCRIPT) $^

clean:
	rm -f $(OBJ) *.elf *.bin

#%.o: %.c
#  $(CC) $(CFLAGS) -c $< -o $@

# GAS emits error when optimization is enabled
CM3/CoreSupport/core_cm3.o: CM3/CoreSupport/core_cm3.c
	$(CC) $(CFLAGS) -O0 -c -o $@ $<
