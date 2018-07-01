################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Source/Widgets/subdir.mk
-include Source/MainWindow/subdir.mk
-include Source/Controllers/subdir.mk
-include Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: exadrums

dependents:
	-cd /home/jeremy/Desktop/Prog/eXaDrums/libeXaDrums/Debug && $(MAKE) all

# Tool invocations
exadrums: $(OBJS) $(USER_OBJS) /home/jeremy/Desktop/Prog/eXaDrums/libeXaDrums/Debug/exadrums.so.0
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++ -o "exadrums" $(OBJS) $(USER_OBJS) $(LIBS) -L"/home/jeremy/Desktop/Prog/eXaDrums/libeXaDrums/Debug" -L../../libeXaDrums/Debug $(shell pkg-config --libs gtkmm-3.0)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) exadrums
	-@echo ' '

.PHONY: all clean dependents
/home/jeremy/Desktop/Prog/eXaDrums/libeXaDrums/Debug/exadrums.so.0:

-include ../makefile.targets
