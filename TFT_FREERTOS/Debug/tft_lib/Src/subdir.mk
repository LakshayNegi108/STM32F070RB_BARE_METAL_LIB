################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tft_lib/Src/fonts.c \
../tft_lib/Src/graphics.c \
../tft_lib/Src/st7783.c \
../tft_lib/Src/touch.c 

OBJS += \
./tft_lib/Src/fonts.o \
./tft_lib/Src/graphics.o \
./tft_lib/Src/st7783.o \
./tft_lib/Src/touch.o 

C_DEPS += \
./tft_lib/Src/fonts.d \
./tft_lib/Src/graphics.d \
./tft_lib/Src/st7783.d \
./tft_lib/Src/touch.d 


# Each subdirectory must supply rules for building sources it contributes
tft_lib/Src/%.o tft_lib/Src/%.su: ../tft_lib/Src/%.c tft_lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F070xB -c -I../Core/Inc -I"E:/STM codes/TFT_FREERTOS/Libraries/Inc" -I"E:/STM codes/TFT_FREERTOS/tft_lib/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-tft_lib-2f-Src

clean-tft_lib-2f-Src:
	-$(RM) ./tft_lib/Src/fonts.d ./tft_lib/Src/fonts.o ./tft_lib/Src/fonts.su ./tft_lib/Src/graphics.d ./tft_lib/Src/graphics.o ./tft_lib/Src/graphics.su ./tft_lib/Src/st7783.d ./tft_lib/Src/st7783.o ./tft_lib/Src/st7783.su ./tft_lib/Src/touch.d ./tft_lib/Src/touch.o ./tft_lib/Src/touch.su

.PHONY: clean-tft_lib-2f-Src

