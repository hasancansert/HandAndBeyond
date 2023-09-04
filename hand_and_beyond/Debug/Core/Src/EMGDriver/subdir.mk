################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/EMGDriver/EMGDriver.c 

C_DEPS += \
./Core/Src/EMGDriver/EMGDriver.d 

OBJS += \
./Core/Src/EMGDriver/EMGDriver.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/EMGDriver/%.o Core/Src/EMGDriver/%.su Core/Src/EMGDriver/%.cyclo: ../Core/Src/EMGDriver/%.c Core/Src/EMGDriver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-EMGDriver

clean-Core-2f-Src-2f-EMGDriver:
	-$(RM) ./Core/Src/EMGDriver/EMGDriver.cyclo ./Core/Src/EMGDriver/EMGDriver.d ./Core/Src/EMGDriver/EMGDriver.o ./Core/Src/EMGDriver/EMGDriver.su

.PHONY: clean-Core-2f-Src-2f-EMGDriver

