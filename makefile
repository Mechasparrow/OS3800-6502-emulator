build: *.cc *.h hexlib/*.h hexlib/*.cc tests/*.cc
	cmake --build build 

test:
	cd build && ctest 

run:
	cd build && ./6502_cs3800_emulator