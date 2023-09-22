################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/PCListener/PCListener.c 

C_DEPS += \
./Drivers/PCListener/PCListener.d 

OBJS += \
./Drivers/PCListener/PCListener.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/PCListener/%.o Drivers/PCListener/%.su Drivers/PCListener/%.cyclo: ../Drivers/PCListener/%.c Drivers/PCListener/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/PCListener -I../Drivers/EMGDriver -I../Drivers/MotorDriver -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-PCListener

clean-Drivers-2f-PCListener:
	-$(RM) ./Drivers/PCListener/PCListener.cyclo ./Drivers/PCListener/PCListener.d ./Drivers/PCListener/PCListener.o ./Drivers/PCListener/PCListener.su

.PHONY: clean-Drivers-2f-PCListener

