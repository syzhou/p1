################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Meeting.c \
../Ordered_container_array.c \
../Ordered_container_list.c \
../Person.c \
../Room.c \
../Utility.c \
../p1_globals.c \
../p1_main.c \
../testContainer1.c 

OBJS += \
./Meeting.o \
./Ordered_container_array.o \
./Ordered_container_list.o \
./Person.o \
./Room.o \
./Utility.o \
./p1_globals.o \
./p1_main.o \
./testContainer1.o 

C_DEPS += \
./Meeting.d \
./Ordered_container_array.d \
./Ordered_container_list.d \
./Person.d \
./Room.d \
./Utility.d \
./p1_globals.d \
./p1_main.d \
./testContainer1.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


