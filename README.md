# OS3800-6502-emulator
Turing Complete 6502 Emulator for the CS3800 class final project.

# Why did I build this project?
I have always been fascinated how first microcomputers were built with simple 8-bit processors like the MOS 6502 processor. I thought it would be a fun exercise to emulate a 6502 processor so that I could later emulate systems such as the NES, Apple I, and the Commodore 64

# Computer requirements
- 64-bit Linux system such as Ubuntu
- GCC compiler
- CMake installed with version 3.14 or higher

# Building the Project
1. Create build folder `cmake -S . -B build`
2. Build emulator `cmake --build build`

# Running the Project
Please ensure that you have Built the project before running. Refer to the **Building the Project** instructions above.

## Example command execution
```bash
./build/6502_cs3800_emulator path/to/program.s19 path/to/programaddresses.addr
```

## Running the Fibonacci example program
```bash
cd test_assembly
./assemble.sh fib/fib.asm
../build/6502_cs3800_emulator fib/fib.s19 fib/addresses.addr
```
Or Docker
```
docker run -it --rm -v `pwd`:/usr/src/emulatorlocal rikorose/gcc-cmake:gcc-11 /bin/bash -c "cp -R /usr/src/emulatorlocal /usr/src/emulator; rm -r /usr/src/emulator/build; cd /usr/src/emulator/; ./fib-docker.sh"
```


^ The result of `$B002` will be `fib(6)`: `0x08`

## Running the Multiply example program
```bash
cd test_assembly
./assemble.sh mul/mul.asm
../build/6502_cs3800_emulator mul/mul.s19 mul/addresses.addr
```
Or Docker
```
docker run -it --rm -v `pwd`:/usr/src/emulatorlocal rikorose/gcc-cmake:gcc-11 /bin/bash -c "cp -R /usr/src/emulatorlocal /usr/src/emulator; rm -r /usr/src/emulator/build; cd /usr/src/emulator/; ./mul-docker.sh"
```
^ The result of `$B002` will be `6 * 3` in hexadecimal: `0x12`

# Running tests
`cd build && ctest`

# Hardware emulation
The software-defined MOS 6502 CPU will be abstracted into a single data structure with a five 8-bit registers (A, X, Y, Stack pointer, Status register) and an 16 bit program counter. Additionally, there will be a data field that will be 64KB in size (or 64,000 characters assuming a character is 1 byte). 

# 6502 implemented operations

## Arithmetic Instructions

The following 6502 arithmetic instructions will be implemented: 
- [x] DEC
- [x] DEX
- [x] DEY
- [x] INC
- [x] INX
- [x] INY
- [x] ADC
- [x] SBC
- [x] CLC
- [x] SEC

## Data Instructions
The following 6502 data instructions will be implemented.  
- [x] LDA
- [x] LDX
- [x] LDY
- [x] STA
- [x] STX
- [x] STY
- [x] TAX
- [x] TXA
- [x] TAY
- [x] TYA

## Conditional Instructions (used for comparing values in branching)
- [X] CMP
- [X] CPX
- [X] CPY

## Branching Instructions
- [X] BCC ; Carry clear
- [X] BCS ; Carry set
- [X] BMI ; Break negative
- [X] BPL ; Break positive
- [x] BVC ; Break overflow clear
- [x] BVS ; Break overflow set
- [x] BEQ ; Break equal
- [x] BNE ; Break not equal
- [X] JMP

# References
Op Code lookup and instruction reference  
https://www.masswerk.at/6502/6502_instruction_set.html

CMake Docker container  
https://github.com/Rikorose/gcc-cmake

6502 Processor Reference Documents and Information  
http://www.6502.org/

VASM assembler  
http://sun.hasenbraten.de/vasm/