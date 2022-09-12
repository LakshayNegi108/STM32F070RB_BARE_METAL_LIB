################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Src/BML_DRIVER.c \
../Libraries/Src/SDCard.c 

OBJS += \
./Libraries/Src/BML_DRIVER.o \
./Libraries/Src/SDCard.o 

C_DEPS += \
./Libraries/Src/BML_DRIVER.d \
./Libraries/Src/SDCard.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Src/%.o Libraries/Src/%.su: ../Libraries/Src/%.c Libraries/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F070xB -c -I../Core/Inc -I"E:/STM codes/TFT_FREERTOS/Libraries/Inc" -I"E:/STM codes/TFT_FREERTOS/tft_lib/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries-2f-Src

clean-Libraries-2f-Src:
	-$(RM) ./Libraries/Src/BML_DRIVER.d ./Libraries/Src/BML_DRIVER.o ./Libraries/Src/BML_DRIVER.su ./Libraries/Src/SDCard.d ./Libraries/Src/SDCard.o ./Libraries/Src/SDCard.su

.PHONY: clean-Libraries-2f-Src

