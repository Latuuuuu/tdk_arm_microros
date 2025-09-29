################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Inc/Control_Lib/arm/Src/arm.cpp 

OBJS += \
./Core/Inc/Control_Lib/arm/Src/arm.o 

CPP_DEPS += \
./Core/Inc/Control_Lib/arm/Src/arm.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/Control_Lib/arm/Src/%.o Core/Inc/Control_Lib/arm/Src/%.su Core/Inc/Control_Lib/arm/Src/%.cyclo: ../Core/Inc/Control_Lib/arm/Src/%.cpp Core/Inc/Control_Lib/arm/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"/home/ling/STM32CubeIDE/workspace_1.19.0/tdk_arm_microros/Core/Inc/uros" -I"/home/ling/STM32CubeIDE/workspace_1.19.0/tdk_arm_microros/Core/Inc/Control_Lib/arm/Inc" -I"/home/ling/STM32CubeIDE/workspace_1.19.0/tdk_arm_microros/Core/Inc/Control_Lib/UART_servo/Inc" -I"/home/ling/STM32CubeIDE/workspace_1.19.0/tdk_arm_microros/Core/Inc/Control_Lib/motor_ctrl/Inc" -I../micro_ros_stm32cubemx_utils/microros_static_library_ide/libmicroros/include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-Control_Lib-2f-arm-2f-Src

clean-Core-2f-Inc-2f-Control_Lib-2f-arm-2f-Src:
	-$(RM) ./Core/Inc/Control_Lib/arm/Src/arm.cyclo ./Core/Inc/Control_Lib/arm/Src/arm.d ./Core/Inc/Control_Lib/arm/Src/arm.o ./Core/Inc/Control_Lib/arm/Src/arm.su

.PHONY: clean-Core-2f-Inc-2f-Control_Lib-2f-arm-2f-Src

