build: 6502_lib.cc 6502_lib.h 6502_main.cc cpu_core_test.cc
	cmake --build build 

test:
	cd build && ctest 

run:
	cd build && ./6502_cs3800_emulator