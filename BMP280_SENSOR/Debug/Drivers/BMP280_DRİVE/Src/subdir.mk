################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BMP280_DRİVE/Src/bmp280.c 

OBJS += \
./Drivers/BMP280_DRİVE/Src/bmp280.o 

C_DEPS += \
./Drivers/BMP280_DRİVE/Src/bmp280.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BMP280_DRİVE/Src/%.o Drivers/BMP280_DRİVE/Src/%.su Drivers/BMP280_DRİVE/Src/%.cyclo: ../Drivers/BMP280_DRİVE/Src/%.c Drivers/BMP280_DRİVE/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/BMP280_DRİVE/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/BMP280_DRİVE -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BMP280_DR-130-VE-2f-Src

clean-Drivers-2f-BMP280_DR-130-VE-2f-Src:
	-$(RM) ./Drivers/BMP280_DRİVE/Src/bmp280.cyclo ./Drivers/BMP280_DRİVE/Src/bmp280.d ./Drivers/BMP280_DRİVE/Src/bmp280.o ./Drivers/BMP280_DRİVE/Src/bmp280.su

.PHONY: clean-Drivers-2f-BMP280_DR-130-VE-2f-Src

