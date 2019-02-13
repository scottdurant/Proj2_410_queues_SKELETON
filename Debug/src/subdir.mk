################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Proj2_410_Queues_Solution.cpp \
../src/dispatcherTester.cpp \
../src/joblistTester.cpp 

OBJS += \
./src/Proj2_410_Queues_Solution.o \
./src/dispatcherTester.o \
./src/joblistTester.o 

CPP_DEPS += \
./src/Proj2_410_Queues_Solution.d \
./src/dispatcherTester.d \
./src/joblistTester.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


