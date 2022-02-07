################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/SPI/subdir.mk
-include MCAL/DIO/subdir.mk
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
SPI_testCaseMaster.lss \

FLASH_IMAGE += \
SPI_testCaseMaster.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: SPI_testCaseMaster.elf secondary-outputs

# Tool invocations
SPI_testCaseMaster.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SPI_testCaseMaster.map -mmcu=atmega32 -o "SPI_testCaseMaster.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SPI_testCaseMaster.lss: SPI_testCaseMaster.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SPI_testCaseMaster.elf  >"SPI_testCaseMaster.lss"
	@echo 'Finished building: $@'
	@echo ' '

SPI_testCaseMaster.hex: SPI_testCaseMaster.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SPI_testCaseMaster.elf  "SPI_testCaseMaster.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SPI_testCaseMaster.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 SPI_testCaseMaster.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SPI_testCaseMaster.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
