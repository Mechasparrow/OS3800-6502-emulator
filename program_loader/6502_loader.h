#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "../hexlib/hex_lib.h"
#include "../6502_lib.h"

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

static const std::map<SRecordType, std::string> SRecordTypeStringMap {
    {SRecordType::Header, "Header"},
    {SRecordType::Data16, "Data16"},
    {SRecordType::Data24, "Data24"},
    {SRecordType::Data32, "Data32"},
    {SRecordType::Reserved, "Reserved"},
    {SRecordType::Count16, "Count16"},
    {SRecordType::Count24, "Count24"}, 
    {SRecordType::StartAddress32, "StartAddress32"},
    {SRecordType::StartAddress24, "StartAddress24"},
    {SRecordType::StartAddress16, "StartAddress16"}, 
    {SRecordType::Unknown, "Unknown"}, 
};

class SRecord {
    public:
        SRecordType recordType;
        uint8_t recordSize;
        uint16_t recordStartingAddress;
        std::vector<uint8_t> recordData; 
        uint8_t checkSum;

        void printRecord();
};

class Loader6502 {
    public:
        Loader6502(std::string fileName);
        ~Loader6502();

        void burnRecords(DataBus * dataBus);
        void readFileContents();

        bool recordRead;
    private: 
        std::string fileName;
        std::ifstream fileStream;
        std::vector<SRecord> records;
        
};