################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib-uIP/sys/stimer.c \
../lib-uIP/sys/ttimer.c 

OBJS += \
./lib-uIP/sys/stimer.o \
./lib-uIP/sys/ttimer.o 

C_DEPS += \
./lib-uIP/sys/stimer.d \
./lib-uIP/sys/ttimer.d 


# Each subdirectory must supply rules for building sources it contributes
lib-uIP/sys/%.o: ../lib-uIP/sys/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\ProgDev\CPP\EclipseWS\freeRTOS\FreeRTOS801\include" -DGCC_MEGA_AVR -Wall -O2 -ffunction-sections -fdata-sections -mcall-prologues -mrelax -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


