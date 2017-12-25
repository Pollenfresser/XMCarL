################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../system/CMSIS/Infineon/XMC4500_series/Source/GCC/startup_XMC4500.S 

OBJS += \
./system/CMSIS/Infineon/XMC4500_series/Source/GCC/startup_XMC4500.o 

S_UPPER_DEPS += \
./system/CMSIS/Infineon/XMC4500_series/Source/GCC/startup_XMC4500.d 


# Each subdirectory must supply rules for building sources it contributes
system/CMSIS/Infineon/XMC4500_series/Source/GCC/%.o: ../system/CMSIS/Infineon/XMC4500_series/Source/GCC/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


