################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MotorDriver/MotorDriver.c 

C_DEPS += \
./Drivers/MotorDriver/MotorDriver.d 

OBJS += \
./Drivers/MotorDriver/MotorDriver.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MotorDriver/%.o Drivers/MotorDriver/%.su Drivers/MotorDriver/%.cyclo: ../Drivers/MotorDriver/%.c Drivers/MotorDriver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/EMGDriver -I../Drivers/MotorDriver -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-MotorDriver

clean-Drivers-2f-MotorDriver:
	-$(RM) ./Drivers/MotorDriver/MotorDriver.cyclo ./Drivers/MotorDriver/MotorDriver.d ./Drivers/MotorDriver/MotorDriver.o ./Drivers/MotorDriver/MotorDriver.su

.PHONY: clean-Drivers-2f-MotorDriver

