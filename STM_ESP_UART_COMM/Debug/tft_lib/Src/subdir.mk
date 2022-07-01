################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tft_lib/Src/graphics.c \
../tft_lib/Src/st7783.c \
../tft_lib/Src/touch.c 

OBJS += \
./tft_lib/Src/graphics.o \
./tft_lib/Src/st7783.o \
./tft_lib/Src/touch.o 

C_DEPS += \
./tft_lib/Src/graphics.d \
./tft_lib/Src/st7783.d \
./tft_lib/Src/touch.d 


# Each subdirectory must supply rules for building sources it contributes
tft_lib/Src/%.o: ../tft_lib/Src/%.c tft_lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F070xB -c -I../Core/Inc -I"E:/STM codes/STM_ESP_UART_COMM/Libraries/Inc" -I"E:/STM codes/STM_ESP_UART_COMM/tft_lib/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

