Hardware emulation
The software-defined MOS 6502 CPU will be abstracted into a single data structure with a five 8-bit registers (A, X, Y, Stack pointer, Status register) and an 16 bit program counter. Additionally, there will be a data field that will be 64KB in size (or 64,000 characters assuming a character is 1 byte). 

# Arithmetic Instructions

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

# Data Instructions
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

# Conditional Instructions (used for comparing values in branching)
- [X] CMP
- [X] CPX
- [X] CPY

# Branching Instructions
- [X] BCC ; Carry clear
- [X] BCS ; Carry set
- [ ] BMI ; Break negative
- [ ] BPL ; Break positive
- [ ] BVC ; Break overflow clear
- [ ] BVS ; Break overflow set
- [ ] BEQ ; Break equal
- [ ] BNE ; Break not equal
- [X] JMP

# Execution 
The program will take the file path to a ASM file (formatted for 6502) and execute its contents. The example execution will be to compute a Fibonacci number.
