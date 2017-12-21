################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Dispatcher.cpp \
../src/LoginAndSignUp.cpp \
../src/Server.cpp \
../src/ServerTicTacToe.cpp \
../src/User.cpp \
../src/md5.cpp 

OBJS += \
./src/Dispatcher.o \
./src/LoginAndSignUp.o \
./src/Server.o \
./src/ServerTicTacToe.o \
./src/User.o \
./src/md5.o 

CPP_DEPS += \
./src/Dispatcher.d \
./src/LoginAndSignUp.d \
./src/Server.d \
./src/ServerTicTacToe.d \
./src/User.d \
./src/md5.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/workspace/final_project/msockets/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


