#include <iostream>
#include <fstream>
#include <forward_list>
#include "../hexlib/hex_lib.h"


//For s19 records: We can assume that
//only S0, S1, S5, and S9 is used
enum SRecordType {
    Header, //s0
    Data16, //s1
    Data24, //s2
    Data32, //s3
    Reserved, //s4
    Count16, //s5
    Count24, //s6
    StartAddress32, //s7 
    StartAddress24, //s8
    StartAddress16, //s9,
    Unknown
};

class SRecord {
    public:
        SRecordType recordType;
        uint8_t recordSize;
        uint16_t recordStartingAddress;
        std::forward_list<uint8_t> recordData; 
        uint8_t checkSum;

        void printRecord();
};

class Loader6502 {
    public:
        Loader6502(std::string fileName);
        ~Loader6502();

        void readFileContents();
    private: 
        std::string fileName;
        std::ifstream fileStream;
};