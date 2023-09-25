cmake_minimum_required(VERSION 3.25)
project(CpuEmuKernel)

add_library(CpuEmuKernel)
target_sources(CpuEmuKernel
	PRIVATE
	src/Types/Node.cpp
	src/Types/Wire.cpp
	src/Units/ALU.cpp
	src/Units/Adder.cpp
	src/Units/Multiplexer.cpp
	src/Units/Registers.cpp
	src/Units/ReadOnlyMemory.cpp
	src/Utils.cpp
)
target_include_directories(CpuEmuKernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/)

add_executable(Driver src/Driver/Driver.cpp)
target_link_libraries(Driver CpuEmuKernel)

