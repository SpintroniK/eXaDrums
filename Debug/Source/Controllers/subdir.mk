################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Controllers/CoachController.cpp \
../Source/Controllers/ConfigController.cpp \
../Source/Controllers/KitController.cpp \
../Source/Controllers/MainController.cpp \
../Source/Controllers/MetronomeController.cpp 

OBJS += \
./Source/Controllers/CoachController.o \
./Source/Controllers/ConfigController.o \
./Source/Controllers/KitController.o \
./Source/Controllers/MainController.o \
./Source/Controllers/MetronomeController.o 

CPP_DEPS += \
./Source/Controllers/CoachController.d \
./Source/Controllers/ConfigController.d \
./Source/Controllers/KitController.d \
./Source/Controllers/MainController.d \
./Source/Controllers/MetronomeController.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Controllers/%.o: ../Source/Controllers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++14 -I../../libeXaDrums -O0 -g3 -Wall -c -fmessage-length=0 $(shell pkg-config --cflags gtkmm-3.0) -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


