################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib_hd44780/hd44780.c 

OBJS += \
./lib_hd44780/hd44780.o 

C_DEPS += \
./lib_hd44780/hd44780.d 


# Each subdirectory must supply rules for building sources it contributes
lib_hd44780/%.o: ../lib_hd44780/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\ProgDev\CPP\EclipseWS\freeRTOS\FreeRTOS801\include" -DGCC_MEGA_AVR -Wall -O2 -ffunction-sections -fdata-sections -mcall-prologues -mrelax -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


