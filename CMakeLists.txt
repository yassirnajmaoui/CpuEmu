cmake_minimum_required(VERSION 3.25)
project(CpuEmuKernel)

SET(CMAKE_CXX_COMPILE_FEATURES -g)

# For Lapce editor, which uses clangd
#SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#SET(CMAKE_CXX_FLAGS "-isystem /usr/include/c++/11 -isystem /usr/include/x86_64-linux-gnu/c++/11 -isystem /usr/include/c++/11/backward -isystem /usr/lib/gcc/x86_64-linux-gnu/11/include -isystem /usr/local/include -isystem /usr/include/x86_64-linux-gnu -isystem /usr/include")

add_library(CpuEmuKernel)
target_sources(CpuEmuKernel
	PRIVATE
	src/Types/Node.cpp
	src/Types/Wire.cpp
	src/Units/Adder.cpp
	src/Units/ALU.cpp
	src/Units/ALUControl.cpp
	src/Units/Controller.cpp
	src/Units/InstructionParser.cpp
	src/Units/Memory.cpp
	src/Units/ReadOnlyMemory.cpp
	src/Units/Relay.cpp
	src/Units/Registers.cpp
	src/Units/RegistersWriter.cpp
	src/Utils.cpp
	src/BitUtils.cpp
	src/BinToString.cpp
	src/RISCV-Instructions.cpp
)
target_include_directories(CpuEmuKernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(Main src/Drivers/Main.cpp)
target_link_libraries(Main CpuEmuKernel)

add_executable(TestInstructionParser src/Drivers/TestInstructionParser.cpp)
target_link_libraries(TestInstructionParser CpuEmuKernel)

add_executable(TestRegisters src/Drivers/TestRegisters.cpp)
target_link_libraries(TestRegisters CpuEmuKernel)

