################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Drivers/RGB_led/RGB_led.c 

OBJS += \
./Core/Drivers/RGB_led/RGB_led.o 

C_DEPS += \
./Core/Drivers/RGB_led/RGB_led.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Drivers/RGB_led/%.o Core/Drivers/RGB_led/%.su Core/Drivers/RGB_led/%.cyclo: ../Core/Drivers/RGB_led/%.c Core/Drivers/RGB_led/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F302x8 -DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=8000000 -DHSI_VALUE=8000000 -DLSI_VALUE=40000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Drivers-2f-RGB_led

clean-Core-2f-Drivers-2f-RGB_led:
	-$(RM) ./Core/Drivers/RGB_led/RGB_led.cyclo ./Core/Drivers/RGB_led/RGB_led.d ./Core/Drivers/RGB_led/RGB_led.o ./Core/Drivers/RGB_led/RGB_led.su

.PHONY: clean-Core-2f-Drivers-2f-RGB_led

