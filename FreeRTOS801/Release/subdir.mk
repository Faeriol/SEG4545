################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../croutine.c \
../event_groups.c \
../list.c \
../queue.c \
../runtTimeStatsTimer.c \
../tasks.c \
../timers.c 

OBJS += \
./croutine.o \
./event_groups.o \
./list.o \
./queue.o \
./runtTimeStatsTimer.o \
./tasks.o \
./timers.o 

C_DEPS += \
./croutine.d \
./event_groups.d \
./list.d \
./queue.d \
./runtTimeStatsTimer.d \
./tasks.d \
./timers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\ProgDev\CPP\EclipseWS\freeRTOS\FreeRTOS801\include" -DGCC_MEGA_AVR -Wall -O2 -ffunction-sections -fdata-sections -mcall-prologues -mrelax -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


