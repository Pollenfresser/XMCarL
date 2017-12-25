################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c 

OBJS += \
./src/main.o 

C_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DXMC4500_F100x1024 -D__FPU_PRESENT -DARM_MATH_CM4 -I"/home/prinzessin/fhtw/xmcarl/XMC/Car/xmclib/inc" -I"/home/prinzessin/fhtw/xmcarl/XMC/Car/system/CMSIS/Include" -I"/home/prinzessin/fhtw/xmcarl/XMC/Car/system/CMSIS/Infineon/XMC4500_series/Include" -I"/home/prinzessin/fhtw/xmcarl/XMC/Car/inc" -I"/home/prinzessin/fhtw/xmcarl/XMC/Car/system" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


