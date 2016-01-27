################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include portable/subdir.mk
-include lib_util/subdir.mk
-include lib_time/subdir.mk
-include lib_rtc/subdir.mk
-include lib_io/subdir.mk
-include lib_inet/subdir.mk
-include lib_iinchip/subdir.mk
-include lib_hd44780/subdir.mk
-include lib_ft800/subdir.mk
-include lib_fatf/subdir.mk
-include lib_ext_ram/subdir.mk
-include lib-uIP/sys/subdir.mk
-include lib-uIP/lib/subdir.mk
-include lib-uIP/apps/subdir.mk
-include lib-uIP/subdir.mk
-include MemMang/subdir.mk
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
libFreeRTOS801.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: libFreeRTOS801.a secondary-outputs

# Tool invocations
libFreeRTOS801.a: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR Archiver'
	avr-ar -r  "libFreeRTOS801.a" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

libFreeRTOS801.lss: libFreeRTOS801.a
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S libFreeRTOS801.a  >"libFreeRTOS801.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: libFreeRTOS801.a
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega2560 libFreeRTOS801.a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(ARCHIVES)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) libFreeRTOS801.a
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
