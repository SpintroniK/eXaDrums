################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/MainWindow/MainWindow.cpp 

OBJS += \
./Source/MainWindow/MainWindow.o 

CPP_DEPS += \
./Source/MainWindow/MainWindow.d 


# Each subdirectory must supply rules for building sources it contributes
Source/MainWindow/%.o: ../Source/MainWindow/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++14 -I../../libeXaDrums -O0 -g3 -Wall -c -fmessage-length=0 $(shell pkg-config --cflags gtkmm-3.0) -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


