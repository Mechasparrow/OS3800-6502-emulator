#include "6502_loader.h"

SRecord parseSRecordString(std::string rawSRecord);
SRecordType parseStringToRecordType(std::string rawSRecordType);

Loader6502::Loader6502(std::string fileName){
    this->fileName = fileName;
    this->fileStream.open(this->fileName);
}

Loader6502::~Loader6502(){
    this->fileStream.close();
}

void Loader6502::readFileContents(){
    std::cout << "Reading the following file: " << this->fileName << std::endl;
    //https://en.wikipedia.org/wiki/SREC_(file_format)

    //Read S type
    std::string sRecord;
    if (this->fileStream.is_open()){
        while (std::getline(this->fileStream, sRecord)){
            SRecord parsedRecord = parseSRecordString(sRecord);
            parsedRecord.printRecord();
            std::cout << std::endl;
        }
    }else{
        std::cout << "Unable to open file" << std::endl;
    }
}

void SRecord::printRecord(){
    std::cout << "Record Type: " << this->recordType << std::endl;
    std::cout << "Record Size: " << (int)this->recordSize << std::endl;
    std::cout << "Record Address: " << byte2doublehex(this->recordStartingAddress) << std::endl;
    std::cout << "Record Data: " << "TODO" << std::endl;
    std::cout << "Record Checksum: " << byte2hex(this->checkSum) << std::endl;
}

SRecord parseSRecordString(std::string rawSRecord){

    SRecord newRecord;

    //TODO
    unsigned int recordStringIdx = 0;
    
    std::string recordTypeString {
        rawSRecord[recordStringIdx],
        rawSRecord[recordStringIdx+1]
    };

    recordStringIdx+=2;
    std::string byteCountString {
        rawSRecord[recordStringIdx], 
        rawSRecord[recordStringIdx+1]
    };

    recordStringIdx+=2;
    std::string addressString {
        rawSRecord[recordStringIdx], 
        rawSRecord[recordStringIdx+1], 
        rawSRecord[recordStringIdx+2], 
        rawSRecord[recordStringIdx+3]
    };
    recordStringIdx+=4;

    newRecord.recordType = parseStringToRecordType(recordTypeString);
    newRecord.recordSize = hex2byte(byteCountString);
    newRecord.recordStartingAddress = hex2doublebyte(addressString);

    std::cout << "Starting data idx: " << recordStringIdx << std::endl;

    //TODO read the data elements

    //TODO read the checksum
    unsigned int recordLength = rawSRecord.length();
    std::string checkSumString {rawSRecord[recordLength-2], rawSRecord[recordLength-1]};
    newRecord.checkSum = hex2byte(checkSumString);

    return newRecord;
}


SRecordType parseStringToRecordType(std::string rawSRecordType){
    //TODO
    return Unknown;
}