################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../motion.c \
../usartSerial.c 

OBJS += \
./motion.o \
./usartSerial.o 

C_DEPS += \
./motion.d \
./usartSerial.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\ProgDev\CPP\EclipseWS\freeRTOS\CEG4166_RTS_Lib\include" -I"D:\ProgDev\CPP\EclipseWS\freeRTOS\FreeRTOS801\include" -DGCC_MEGA_AVR -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


