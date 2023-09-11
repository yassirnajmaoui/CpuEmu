cmake_minimum_required(VERSION 3.0.0)
project(CpuEmuKernel VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

SET(SOURCE_FILES
	src/Types/Node.cpp
	src/Units/AdderNode.cpp
	src/Units/ALU.cpp
	src/Types/Wire.cpp
	)

add_library(CpuEmuKernel ${SOURCE_FILES})
target_include_directories(CpuEmuKernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_executable(Driver src/main.cpp)
target_include_directories(Driver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include/)
target_link_libraries(Driver CpuEmuKernel)
