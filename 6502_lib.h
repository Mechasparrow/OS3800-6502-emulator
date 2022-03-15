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

        unsigned char RAM[RAM_SIZE];
};

CPU6502 init_CPU();