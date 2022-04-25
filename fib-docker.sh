#!/bin/bash

# Build the program
cmake -S . -B build 1> /dev/null
cmake --build build 1> /dev/null

# Assemble the fib asm
cd ./test_assembly
./assemble.sh fib/fib.asm 1> /dev/null

# Run the fib asm program
../build/6502_cs3800_emulator fib/fib.s19 fib/addresses.addr