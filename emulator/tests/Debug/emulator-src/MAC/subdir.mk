################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/michael/Projects/eclipse/C++/80211ah/emulator/src/MAC/MacPdu.cpp 

OBJS += \
./emulator-src/MAC/MacPdu.o 

CPP_DEPS += \
./emulator-src/MAC/MacPdu.d 


# Each subdirectory must supply rules for building sources it contributes
emulator-src/MAC/MacPdu.o: /home/michael/Projects/eclipse/C++/80211ah/emulator/src/MAC/MacPdu.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_GXX_EXPERIMENTAL_CXX0X_ -D__GXX_EXPERIMENTAL_CXX0X__ -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/data" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/tests/src/PHY/Convertors" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/MAC" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/OSI" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/PHY" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/PHY/Convertors" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/contrib/gtests/include" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/configuration/parser" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/configuration/parser" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/configuration" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/tests/src/configuration" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/configuration/validator" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/configuration/manager" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/configuration/defs" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/tests/src/testUtils" -I"/home/michael/Projects/eclipse/C++/80211ah/emulator/src/log" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


