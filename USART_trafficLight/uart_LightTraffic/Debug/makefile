################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/USART/subdir.mk
-include MCAL/TIMERS/subdir.mk
-include MCAL/DIO/subdir.mk
-include ECUAL/LED/subdir.mk
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
uart_LightTraffic.lss \

FLASH_IMAGE += \
uart_LightTraffic.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: uart_LightTraffic.elf secondary-outputs

# Tool invocations
uart_LightTraffic.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,uart_LightTraffic.map -mmcu=atmega32 -o "uart_LightTraffic.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

uart_LightTraffic.lss: uart_LightTraffic.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S uart_LightTraffic.elf  >"uart_LightTraffic.lss"
	@echo 'Finished building: $@'
	@echo ' '

uart_LightTraffic.hex: uart_LightTraffic.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex uart_LightTraffic.elf  "uart_LightTraffic.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: uart_LightTraffic.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 uart_LightTraffic.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) uart_LightTraffic.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
