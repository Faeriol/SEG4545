################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib_iinchip/md5.c \
../lib_iinchip/socket.c \
../lib_iinchip/socket_util.c \
../lib_iinchip/w5100.c \
../lib_iinchip/w5200.c 

OBJS += \
./lib_iinchip/md5.o \
./lib_iinchip/socket.o \
./lib_iinchip/socket_util.o \
./lib_iinchip/w5100.o \
./lib_iinchip/w5200.o 

C_DEPS += \
./lib_iinchip/md5.d \
./lib_iinchip/socket.d \
./lib_iinchip/socket_util.d \
./lib_iinchip/w5100.d \
./lib_iinchip/w5200.d 


# Each subdirectory must supply rules for building sources it contributes
lib_iinchip/%.o: ../lib_iinchip/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\ProgDev\CPP\EclipseWS\freeRTOS\FreeRTOS801\include" -DGCC_MEGA_AVR -Wall -O2 -ffunction-sections -fdata-sections -mcall-prologues -mrelax -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


