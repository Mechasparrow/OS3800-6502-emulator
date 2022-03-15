#include "6502_lib.h"

CPU6502 init_CPU(){
    CPU6502 newCpu;
    newCpu.A = (unsigned char)0;
    newCpu.PC[0] = (unsigned char)0;
    newCpu.PC[1] = (unsigned char)0;
    newCpu.X = (unsigned char)0;
    newCpu.Y = (unsigned char)0;
    newCpu.flags = (unsigned char)0;
    newCpu.SP = (unsigned char)0;

    return newCpu;
}