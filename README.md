# OS3800-6502-emulator
Turing Complete 6502 Emulator for the CS3800 class final project.

# Computer requirements
- 64-bit Linux system such as Ubuntu
- GCC compiler
- CMake installed with version 3.14 or higher


# Building the Project
1. Create build folder `cmake -S . -B build`
2. Build emulator `cmake --build build`

# Running the Project


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
- [ ] BEQ ; Break equal
- [ ] BNE ; Break not equal
- [X] JMP

# Execution 
The program will take the file path to a ASM file (formatted for 6502) and execute its contents. The example execution will be to compute a Fibonacci number.
