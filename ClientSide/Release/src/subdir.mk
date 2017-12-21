################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Client.cpp \
../src/Peer2Peer.cpp \
../src/TicTacToe.cpp 

OBJS += \
./src/Client.o \
./src/Peer2Peer.o \
./src/TicTacToe.o 

CPP_DEPS += \
./src/Client.d \
./src/Peer2Peer.d \
./src/TicTacToe.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -U__cplusplus -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


