cmake_minimum_required(VERSION 3.25)
project(CpuEmuKernel)

SET(CMAKE_CXX_COMPILE_FEATURES -g)

SET(ADD_GUI on)

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

if(ADD_GUI)
	add_executable(CpuGui)
	target_sources(CpuGui
		PRIVATE
		src/Drivers/Gui/main.cpp
		src/Drivers/Gui/imgui.cpp
		src/Drivers/Gui/imgui_impl_glfw.cpp
		src/Drivers/Gui/imgui_impl_opengl3.cpp
		src/Drivers/Gui/imgui_widgets.cpp
		src/Drivers/Gui/imgui_draw.cpp
		src/Drivers/Gui/imgui_tables.cpp
		src/Drivers/Gui/imgui_demo.cpp
		src/Drivers/Gui/imnodes.cpp
		)
	target_link_libraries(CpuGui CpuEmuKernel)
	target_link_libraries(CpuGui glfw)
	find_package(OpenGL)
	target_link_libraries(CpuGui OpenGL)
endif()
