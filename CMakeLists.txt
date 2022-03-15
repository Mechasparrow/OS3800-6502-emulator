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

add_executable(
	6502_cs3800_emulator
	6502_main.cc
)

add_library(
	6502_lib
	6502_lib.cc
)

add_executable(
	cpu_core_tests
	cpu_core_test.cc
)

target_link_libraries(
	cpu_core_tests
	6502_lib
	gtest_main
)

include(GoogleTest)
gtest_discover_tests(cpu_core_tests)
