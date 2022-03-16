#include "6502_lib.h"

CPU6502::CPU6502() {
    A = (unsigned char)0;
    PC[0] = (unsigned char)0;
    PC[1] = (unsigned char)0;
    X = (unsigned char)0;
    Y = (unsigned char)0;
    flags = (unsigned char)0;
    SP = (unsigned char)0;
}

DataBus::DataBus() {
    for (unsigned int i = 0; i < RAM_SIZE;i++){
        RAM[i] = (unsigned char)0;
    }
}