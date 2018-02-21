################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Widgets/Fader.cpp \
../Source/Widgets/InstrumentSelector.cpp \
../Source/Widgets/SoundTypeAndPath.cpp \
../Source/Widgets/TriggerIdAndLocation.cpp \
../Source/Widgets/TriggerSelector.cpp 

OBJS += \
./Source/Widgets/Fader.o \
./Source/Widgets/InstrumentSelector.o \
./Source/Widgets/SoundTypeAndPath.o \
./Source/Widgets/TriggerIdAndLocation.o \
./Source/Widgets/TriggerSelector.o 

CPP_DEPS += \
./Source/Widgets/Fader.d \
./Source/Widgets/InstrumentSelector.d \
./Source/Widgets/SoundTypeAndPath.d \
./Source/Widgets/TriggerIdAndLocation.d \
./Source/Widgets/TriggerSelector.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Widgets/%.o: ../Source/Widgets/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++14 -I../../libeXaDrums -O0 -g3 -Wall -c -fmessage-length=0 $(shell pkg-config --cflags gtkmm-3.0) -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


