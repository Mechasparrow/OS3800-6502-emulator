cmake_minimum_required(VERSION 3.14)
project(6502_emulator_os3800)

# Google test requires C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/hexlib)
include_directories(${PROJECT_SOURCE_DIR})

add_executable(
	6502_cs3800_emulator
	src/6502_main.cc
)

add_library(
	input_validation
	src/input_validation.cc
)

add_library(
	6502_loader
	src/program_loader/6502_loader.cc
)

add_library(
	hex_lib
	src/hexlib/hex_lib.cc
)

add_library(
	asm_commands
	src/asm_commands.cc
)

add_library(
	6502_lib
	src/6502_lib.cc
)

include_directories(${PROJECT_SOURCE_DIR}/tests)

add_executable(
	cpu_core_tests
	src/tests/cpu_core_test.cc
)

add_executable(
	asm_commands_tests
	src/tests/asm_commands_test.cc
)

add_executable(
	hex_tests
	src/tests/hex_tests.cc
)

target_link_libraries(
	cpu_core_tests
	6502_lib
	gtest_main
)

target_link_libraries(
	hex_tests
	hex_lib
	gtest_main
)

target_link_libraries(
	6502_loader
	hex_lib
)

target_link_libraries(
	asm_commands
	6502_lib
	hex_lib
)

target_link_libraries(
	6502_cs3800_emulator
	input_validation
	asm_commands
	6502_loader
)

target_link_libraries(
	asm_commands_tests
	asm_commands
	6502_lib
	gtest_main
)


include(GoogleTest)
gtest_discover_tests(cpu_core_tests)
gtest_discover_tests(hex_tests)
gtest_discover_tests(asm_commands_tests)
