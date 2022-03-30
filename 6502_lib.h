#include <iostream>

#define RAM_SIZE 64000

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
};