################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USER/gpio_wrapper.c \
../USER/gw1ns4c_it.c \
../USER/lcd_hd44780.c \
../USER/main.c 

OBJS += \
./USER/gpio_wrapper.o \
./USER/gw1ns4c_it.o \
./USER/lcd_hd44780.o \
./USER/main.o 

C_DEPS += \
./USER/gpio_wrapper.d \
./USER/gw1ns4c_it.d \
./USER/lcd_hd44780.d \
./USER/main.d 


# Each subdirectory must supply rules for building sources it contributes
USER/%.o: ../USER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Users\trashcan\Documents\Gowin\MCU_Designer\cm3_1602_lcd\CORE" -I"C:\Users\trashcan\Documents\Gowin\MCU_Designer\cm3_1602_lcd\PERIPHERAL\Includes" -I"C:\Users\trashcan\Documents\Gowin\MCU_Designer\cm3_1602_lcd\SYSTEM" -I"C:\Users\trashcan\Documents\Gowin\MCU_Designer\cm3_1602_lcd\USER" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


