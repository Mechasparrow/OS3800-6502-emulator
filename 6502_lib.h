#include <iostream>

#ifndef CPU
#define CPU

#define RAM_SIZE 65536


class CPU6502 {
    public:
        uint16_t PC;
        uint8_t A;
        uint8_t X;
        uint8_t Y;
        uint8_t SP;
        uint8_t flags;

        CPU6502();
};

class DataBus {
    public:
        uint8_t RAM[RAM_SIZE];
        DataBus();

        uint8_t Read(uint16_t address);
        void Write(uint16_t address, uint8_t value);
};

#endif