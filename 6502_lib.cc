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

uint8_t DataBus::Read(uint16_t address){
    return RAM[address];
}

void DataBus::Write(uint16_t address, uint8_t data){
    RAM[address] = data;
}
