################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
CEG4166RTS_TestLib.lss \

FLASH_IMAGE += \
CEG4166RTS_TestLib.hex \

EEPROM_IMAGE += \
CEG4166RTS_TestLib.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: CEG4166RTS_TestLib.elf secondary-outputs

dependents:
	-cd D:/ProgDev/CPP/EclipseWS/freeRTOS/FreeRTOS801/Release && $(MAKE) all
	-cd D:/ProgDev/CPP/EclipseWS/freeRTOS/CEG4166_RTS_Lib/Release && $(MAKE) all

# Tool invocations
CEG4166RTS_TestLib.elf: $(OBJS) $(USER_OBJS) D:/ProgDev/CPP/EclipseWS/freeRTOS/FreeRTOS801/Release/libFreeRTOS801.a D:/ProgDev/CPP/EclipseWS/freeRTOS/CEG4166_RTS_Lib/Release/libCEG4166_RTS_Lib.a
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,CEG4166RTS_TestLib.map --gc-sections -Wl -L"D:\ProgDev\CPP\EclipseWS\freeRTOS\FreeRTOS801\Release" -L"D:\ProgDev\CPP\EclipseWS\freeRTOS\CEG4166_RTS_Lib\Release" -mmcu=atmega2560 -o "CEG4166RTS_TestLib.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

CEG4166RTS_TestLib.lss: CEG4166RTS_TestLib.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S CEG4166RTS_TestLib.elf  >"CEG4166RTS_TestLib.lss"
	@echo 'Finished building: $@'
	@echo ' '

CEG4166RTS_TestLib.hex: CEG4166RTS_TestLib.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex CEG4166RTS_TestLib.elf  "CEG4166RTS_TestLib.hex"
	@echo 'Finished building: $@'
	@echo ' '

CEG4166RTS_TestLib.eep: CEG4166RTS_TestLib.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex CEG4166RTS_TestLib.elf  "CEG4166RTS_TestLib.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: CEG4166RTS_TestLib.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega2560 CEG4166RTS_TestLib.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) CEG4166RTS_TestLib.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:
D:/ProgDev/CPP/EclipseWS/freeRTOS/FreeRTOS801/Release/libFreeRTOS801.a:
D:/ProgDev/CPP/EclipseWS/freeRTOS/CEG4166_RTS_Lib/Release/libCEG4166_RTS_Lib.a:

-include ../makefile.targets
