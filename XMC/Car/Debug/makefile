################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include xmclib/src/subdir.mk
-include system/CMSIS/Infineon/XMC4500_series/Source/GCC/subdir.mk
-include system/CMSIS/Infineon/XMC4500_series/Source/subdir.mk
-include system/CMSIS/Infineon/Lib/subdir.mk
-include system/CMSIS/DSP_Lib/Source/TransformFunctions/subdir.mk
-include system/CMSIS/DSP_Lib/Source/SupportFunctions/subdir.mk
-include system/CMSIS/DSP_Lib/Source/StatisticsFunctions/subdir.mk
-include system/CMSIS/DSP_Lib/Source/MatrixFunctions/subdir.mk
-include system/CMSIS/DSP_Lib/Source/FilteringFunctions/subdir.mk
-include system/CMSIS/DSP_Lib/Source/FastMathFunctions/subdir.mk
-include system/CMSIS/DSP_Lib/Source/ControllerFunctions/subdir.mk
-include system/CMSIS/DSP_Lib/Source/ComplexMathFunctions/subdir.mk
-include system/CMSIS/DSP_Lib/Source/CommonTables/subdir.mk
-include system/CMSIS/DSP_Lib/Source/BasicMathFunctions/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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
SECONDARY_FLASH += \
xmc4500_if_test.hex \

SECONDARY_SIZE += \
xmc4500_if_test.siz \


# All Target
all: xmc4500_if_test.elf secondary-outputs

# Tool invocations
xmc4500_if_test.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM GNU C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "/home/prinzessin/fhtw/xmcarl/XMC/Car/system/CMSIS/Infineon/XMC4500_series/Source/GCC/XMC4500x1024.ld" -nostartfiles -Xlinker --gc-sections -L"/home/prinzessin/fhtw/xmcarl/XMC/Car/system/CMSIS/Infineon/XMC4500_series/Source/GCC" -L"/home/prinzessin/fhtw/xmcarl/XMC/Car/system/CMSIS/Infineon/Lib" -Wl,-Map,"xmc4500_if_test.map" -o "xmc4500_if_test.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

xmc4500_if_test.hex: xmc4500_if_test.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex -j .text -j .data "xmc4500_if_test.elf"  "xmc4500_if_test.hex"
	@echo 'Finished building: $@'
	@echo ' '

xmc4500_if_test.siz: xmc4500_if_test.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley --totals "xmc4500_if_test.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) xmc4500_if_test.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
