################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/michael/Projects/eclipse/C++/80211ah/emulator/src/configuration/CommandLineOptionsManager.cpp \
/home/michael/Projects/eclipse/C++/80211ah/emulator/src/configuration/CommandLineOptionsParser.cpp 

OBJS += \
./emulator-src/configuration/CommandLineOptionsManager.o \
./emulator-src/configuration/CommandLineOptionsParser.o 

CPP_DEPS += \
./emulator-src/configuration/CommandLineOptionsManager.d \
./emulator-src/configuration/CommandLineOptionsParser.d 


# Each subdirectory must supply rules for building sources it contributes
emulator-src/configuration/CommandLineOptionsManager.o: /home/michael/Projects/eclipse/C++/80211ah/emulator/src/configuration/CommandLineOptionsManager.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_GXX_EXPERIMENTAL_CXX0X_ -D__GXX_EXPERIMENTAL_CXX0X__ -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/data" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/tests/src/PHY/Convertors" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/MAC" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/OSI" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/PHY" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/PHY/Convertors" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/contrib/gtests/include" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/tests/src/configuration" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/configuration" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emulator-src/configuration/CommandLineOptionsParser.o: /home/michael/Projects/eclipse/C++/80211ah/emulator/src/configuration/CommandLineOptionsParser.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_GXX_EXPERIMENTAL_CXX0X_ -D__GXX_EXPERIMENTAL_CXX0X__ -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/data" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/tests/src/PHY/Convertors" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/MAC" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/OSI" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/PHY" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/PHY/Convertors" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/contrib/gtests/include" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/tests/src/configuration" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/configuration" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


