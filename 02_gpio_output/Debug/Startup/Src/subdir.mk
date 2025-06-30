################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Startup/Src/main.c \
../Startup/Src/syscalls.c \
../Startup/Src/sysmem.c 

OBJS += \
./Startup/Src/main.o \
./Startup/Src/syscalls.o \
./Startup/Src/sysmem.o 

C_DEPS += \
./Startup/Src/main.d \
./Startup/Src/syscalls.d \
./Startup/Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/Src/%.o Startup/Src/%.su Startup/Src/%.cyclo: ../Startup/Src/%.c Startup/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DSTM32F446xx -c -I../Inc -I"C:/Users/stoff/Documents/Stm32_Baremetal_Course/F4_chip_headers/F4_chip_headers/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/stoff/Documents/Stm32_Baremetal_Course/F4_chip_headers/F4_chip_headers/chip_headers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Startup-2f-Src

clean-Startup-2f-Src:
	-$(RM) ./Startup/Src/main.cyclo ./Startup/Src/main.d ./Startup/Src/main.o ./Startup/Src/main.su ./Startup/Src/syscalls.cyclo ./Startup/Src/syscalls.d ./Startup/Src/syscalls.o ./Startup/Src/syscalls.su ./Startup/Src/sysmem.cyclo ./Startup/Src/sysmem.d ./Startup/Src/sysmem.o ./Startup/Src/sysmem.su

.PHONY: clean-Startup-2f-Src

