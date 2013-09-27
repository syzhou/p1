################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../test/Ordered_container_demo1.c \
../test/Ordered_container_demo2.c 

OBJS += \
./test/Ordered_container_demo1.o \
./test/Ordered_container_demo2.o 

C_DEPS += \
./test/Ordered_container_demo1.d \
./test/Ordered_container_demo2.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


