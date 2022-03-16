#include <iostream>

#define RAM_SIZE 64000

class CPU6502 {
    public:
        unsigned char PC[2];
        unsigned char A;
        unsigned char X;
        unsigned char Y;
        unsigned char SP;
        unsigned char flags;

        CPU6502();
};

class DataBus {
    public:
        unsigned char RAM[RAM_SIZE];

        DataBus();
};