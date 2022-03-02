################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/capacitive_touch_sensor.c \
../source/gpio_switch.c \
../source/main.c \
../source/mtb.c \
../source/pwm.c \
../source/semihost_hardfault.c \
../source/statemachine.c \
../source/systick_timer.c 

OBJS += \
./source/capacitive_touch_sensor.o \
./source/gpio_switch.o \
./source/main.o \
./source/mtb.o \
./source/pwm.o \
./source/semihost_hardfault.o \
./source/statemachine.o \
./source/systick_timer.o 

C_DEPS += \
./source/capacitive_touch_sensor.d \
./source/gpio_switch.d \
./source/main.d \
./source/mtb.d \
./source/pwm.d \
./source/semihost_hardfault.d \
./source/statemachine.d \
./source/systick_timer.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"C:\Users\Visalakshmi\Downloads\ECEN5813-Asignment4-main\ECEN5813-Asignment4-main\board" -I"C:\Users\Visalakshmi\Downloads\ECEN5813-Asignment4-main\ECEN5813-Asignment4-main\source" -I"C:\Users\Visalakshmi\Downloads\ECEN5813-Asignment4-main\ECEN5813-Asignment4-main" -I"C:\Users\Visalakshmi\Downloads\ECEN5813-Asignment4-main\ECEN5813-Asignment4-main\drivers" -I"C:\Users\Visalakshmi\Downloads\ECEN5813-Asignment4-main\ECEN5813-Asignment4-main\CMSIS" -I"C:\Users\Visalakshmi\Downloads\ECEN5813-Asignment4-main\ECEN5813-Asignment4-main\utilities" -I"C:\Users\Visalakshmi\Downloads\ECEN5813-Asignment4-main\ECEN5813-Asignment4-main\startup" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


