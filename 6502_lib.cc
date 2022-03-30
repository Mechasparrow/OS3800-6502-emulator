#include "6502_lib.h"

CPU6502::CPU6502() {
    A = 0;
    PC = 0;
    X = 0;
    Y = 0;
    flags = 0;
    SP = 0;
}

DataBus::DataBus() {
    for (unsigned int i = 0; i < RAM_SIZE;i++){
        RAM[i] = 0;
    }
}