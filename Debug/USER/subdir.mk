################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USER/gw1ns4c_it.c \
../USER/main.c 

OBJS += \
./USER/gw1ns4c_it.o \
./USER/main.o 

C_DEPS += \
./USER/gw1ns4c_it.d \
./USER/main.d 


# Each subdirectory must supply rules for building sources it contributes
USER/%.o: ../USER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Users\Dorian\Documents\MCU_Projects\cm3_1602_lcd\CORE" -I"C:\Users\Dorian\Documents\MCU_Projects\cm3_1602_lcd\PERIPHERAL\Includes" -I"C:\Users\Dorian\Documents\MCU_Projects\cm3_1602_lcd\SYSTEM" -I"C:\Users\Dorian\Documents\MCU_Projects\cm3_1602_lcd\USER" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


