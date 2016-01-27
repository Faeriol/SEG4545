################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib-uIP/apps/dhcpc.c \
../lib-uIP/apps/simple-httpd.c \
../lib-uIP/apps/tcp-apps.c \
../lib-uIP/apps/udp-apps.c 

OBJS += \
./lib-uIP/apps/dhcpc.o \
./lib-uIP/apps/simple-httpd.o \
./lib-uIP/apps/tcp-apps.o \
./lib-uIP/apps/udp-apps.o 

C_DEPS += \
./lib-uIP/apps/dhcpc.d \
./lib-uIP/apps/simple-httpd.d \
./lib-uIP/apps/tcp-apps.d \
./lib-uIP/apps/udp-apps.d 


# Each subdirectory must supply rules for building sources it contributes
lib-uIP/apps/%.o: ../lib-uIP/apps/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\ProgDev\CPP\EclipseWS\freeRTOS\FreeRTOS801\include" -DGCC_MEGA_AVR -Wall -O2 -ffunction-sections -fdata-sections -mcall-prologues -mrelax -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


