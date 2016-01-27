################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib_fatf/ccsbcs.c \
../lib_fatf/diskio.c \
../lib_fatf/ff.c 

OBJS += \
./lib_fatf/ccsbcs.o \
./lib_fatf/diskio.o \
./lib_fatf/ff.o 

C_DEPS += \
./lib_fatf/ccsbcs.d \
./lib_fatf/diskio.d \
./lib_fatf/ff.d 


# Each subdirectory must supply rules for building sources it contributes
lib_fatf/%.o: ../lib_fatf/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\ProgDev\CPP\EclipseWS\freeRTOS\FreeRTOS801\include" -DGCC_MEGA_AVR -Wall -O2 -ffunction-sections -fdata-sections -mcall-prologues -mrelax -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


