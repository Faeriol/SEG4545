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
libCEG4166_RTS_Lib.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: libCEG4166_RTS_Lib.a secondary-outputs

dependents:
	-cd D:/ProgDev/CPP/EclipseWS/freeRTOS/FreeRTOS801/Release && $(MAKE) all

# Tool invocations
libCEG4166_RTS_Lib.a: $(OBJS) D:/ProgDev/CPP/EclipseWS/freeRTOS/FreeRTOS801/Release/libFreeRTOS801.a
	@echo 'Building target: $@'
	@echo 'Invoking: AVR Archiver'
	avr-ar -r  "libCEG4166_RTS_Lib.a" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

libCEG4166_RTS_Lib.lss: libCEG4166_RTS_Lib.a
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S libCEG4166_RTS_Lib.a  >"libCEG4166_RTS_Lib.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: libCEG4166_RTS_Lib.a
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega2560 libCEG4166_RTS_Lib.a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(ARCHIVES)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) libCEG4166_RTS_Lib.a
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:
D:/ProgDev/CPP/EclipseWS/freeRTOS/FreeRTOS801/Release/libFreeRTOS801.a:

-include ../makefile.targets
