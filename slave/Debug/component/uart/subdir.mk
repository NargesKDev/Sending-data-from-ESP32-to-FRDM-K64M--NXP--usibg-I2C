################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/fsl_adapter_uart.c 

C_DEPS += \
./component/uart/fsl_adapter_uart.d 

OBJS += \
./component/uart/fsl_adapter_uart.o 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c component/uart/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFRDM_K64F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_OS_BAREMETAL -I"C:\Users\nkurk\Desktop\CProgramming\I2C\i2c\i2c\interrupt\esp-frdm\slave\utilities" -I"C:\Users\nkurk\Desktop\CProgramming\I2C\i2c\i2c\interrupt\esp-frdm\slave\drivers" -I"C:\Users\nkurk\Desktop\CProgramming\I2C\i2c\i2c\interrupt\esp-frdm\slave\device" -I"C:\Users\nkurk\Desktop\CProgramming\I2C\i2c\i2c\interrupt\esp-frdm\slave\component\uart" -I"C:\Users\nkurk\Desktop\CProgramming\I2C\i2c\i2c\interrupt\esp-frdm\slave\component\lists" -I"C:\Users\nkurk\Desktop\CProgramming\I2C\i2c\i2c\interrupt\esp-frdm\slave\CMSIS" -I"C:\Users\nkurk\Desktop\CProgramming\I2C\i2c\i2c\interrupt\esp-frdm\slave\source" -I"C:\Users\nkurk\Desktop\CProgramming\I2C\i2c\i2c\interrupt\esp-frdm\slave\board" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-uart

clean-component-2f-uart:
	-$(RM) ./component/uart/fsl_adapter_uart.d ./component/uart/fsl_adapter_uart.o

.PHONY: clean-component-2f-uart

