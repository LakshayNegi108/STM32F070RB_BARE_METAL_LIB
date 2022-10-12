################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/tft_lib/Src/fonts.c \
../Libraries/tft_lib/Src/graphics.c \
../Libraries/tft_lib/Src/st7783.c \
../Libraries/tft_lib/Src/touch.c 

OBJS += \
./Libraries/tft_lib/Src/fonts.o \
./Libraries/tft_lib/Src/graphics.o \
./Libraries/tft_lib/Src/st7783.o \
./Libraries/tft_lib/Src/touch.o 

C_DEPS += \
./Libraries/tft_lib/Src/fonts.d \
./Libraries/tft_lib/Src/graphics.d \
./Libraries/tft_lib/Src/st7783.d \
./Libraries/tft_lib/Src/touch.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/tft_lib/Src/%.o Libraries/tft_lib/Src/%.su: ../Libraries/tft_lib/Src/%.c Libraries/tft_lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F070xB -c -I../Core/Inc -I"E:/STM codes/TFT Library Check/Libraries/SDCardLib/Inc" -I"E:/STM codes/TFT Library Check/FATFS/Target" -I"E:/STM codes/TFT Library Check/FATFS/App" -I"E:/STM codes/TFT Library Check/Middlewares/Third_Party/FatFs/src" -I"E:/STM codes/TFT Library Check/Libraries/BML_DRIVERS/Inc" -I"E:/STM codes/TFT Library Check/Libraries/tft_lib/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries-2f-tft_lib-2f-Src

clean-Libraries-2f-tft_lib-2f-Src:
	-$(RM) ./Libraries/tft_lib/Src/fonts.d ./Libraries/tft_lib/Src/fonts.o ./Libraries/tft_lib/Src/fonts.su ./Libraries/tft_lib/Src/graphics.d ./Libraries/tft_lib/Src/graphics.o ./Libraries/tft_lib/Src/graphics.su ./Libraries/tft_lib/Src/st7783.d ./Libraries/tft_lib/Src/st7783.o ./Libraries/tft_lib/Src/st7783.su ./Libraries/tft_lib/Src/touch.d ./Libraries/tft_lib/Src/touch.o ./Libraries/tft_lib/Src/touch.su

.PHONY: clean-Libraries-2f-tft_lib-2f-Src

