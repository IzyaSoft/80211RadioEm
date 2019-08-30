################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emulator-src/log/subdir.mk
-include emulator-src/data/subdir.mk
-include emulator-src/configuration/validator/subdir.mk
-include emulator-src/configuration/parser/subdir.mk
-include emulator-src/configuration/manager/subdir.mk
-include emulator-src/PHY/Convertors/subdir.mk
-include emulator-src/PHY/subdir.mk
-include emulator-src/MAC/subdir.mk
-include emulator-src/subdir.mk
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
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: emulatorTests

# Tool invocations
emulatorTests: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L"/home/michael/Projects/eclipse/C++/80211ah/emulator/contrib/gtests" -o "emulatorTests" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) emulatorTests
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
