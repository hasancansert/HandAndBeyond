################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/EMGDriver/EMGDriver.c 

C_DEPS += \
./Drivers/EMGDriver/EMGDriver.d 

OBJS += \
./Drivers/EMGDriver/EMGDriver.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/EMGDriver/%.o Drivers/EMGDriver/%.su Drivers/EMGDriver/%.cyclo: ../Drivers/EMGDriver/%.c Drivers/EMGDriver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/EMGDriver -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-EMGDriver

clean-Drivers-2f-EMGDriver:
	-$(RM) ./Drivers/EMGDriver/EMGDriver.cyclo ./Drivers/EMGDriver/EMGDriver.d ./Drivers/EMGDriver/EMGDriver.o ./Drivers/EMGDriver/EMGDriver.su

.PHONY: clean-Drivers-2f-EMGDriver

