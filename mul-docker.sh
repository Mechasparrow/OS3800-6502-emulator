#!/bin/bash

# Build the program
cmake -S . -B build 1> /dev/null
cmake --build build 1> /dev/null

# Assemble the mul asm
cd ./test_assembly
./assemble.sh mul/mul.asm 1> /dev/null

# Run the mul asm program
../build/6502_cs3800_emulator mul/mul.s19 mul/addresses.addr
