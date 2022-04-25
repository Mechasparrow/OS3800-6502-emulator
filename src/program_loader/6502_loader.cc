#include "6502_loader.h"

SRecord parseSRecordString(std::string rawSRecord);
SRecordType parseStringToRecordType(std::string rawSRecordType);

void Loader6502::sharedInit(std::string fileName){
    this->fileStream.open(fileName);
    this->readProgram();
}

Loader6502::Loader6502(std::string fileName){
    this->sharedInit(fileName);    
}

Loader6502::Loader6502(std::string fileName, std::string addressFileName){
    this->sharedInit(fileName);

    this->addressFileStream.open(addressFileName);
    this->readAddresses();
}

Loader6502::~Loader6502(){
    if (this->fileStream.is_open()){
        this->fileStream.close();
    }

    if (this->addressFileStream.is_open()){
        this->addressFileStream.close();
    }
}

//burn into RAM
uint16_t Loader6502::burn(DataBus * dataBus){

    dataBus->addressesToExamine = this->addressesToExamine;

    uint16_t addressIter = hex2doublebyte("0000");
    for (addressIter = hex2doublebyte("0000"); byte2doublehex(addressIter+1) != "0000"; addressIter++){
        dataBus->Write(addressIter, hex2byte("EA"));
    }

    for (SRecord record : this->records){
        if (record.recordType != SRecordType::Data16){
            continue;
        }

        uint16_t addressToWrite = record.recordStartingAddress;

        for (uint8_t dataElem : record.recordData){
            dataBus->Write(addressToWrite, dataElem);
            addressToWrite += 1;
        }
    }

    return this->records.at(this->records.size()-1).recordStartingAddress;
}

void Loader6502::readProgram(){
    //https://en.wikipedia.org/wiki/SREC_(file_format)

    //Read S type
    std::string sRecord;
    if (this->fileStream.is_open()){
        while (std::getline(this->fileStream, sRecord)){
            SRecord parsedRecord = parseSRecordString(sRecord);
            this->records.insert(this->records.end(), parsedRecord);
        }

        this->recordRead = true;
    }else{
        std::cout << "Unable to open file" << std::endl;
    }
}

void Loader6502::readAddresses(){
//https://en.wikipedia.org/wiki/SREC_(file_format)

    //Read S type
    std::string addressLine;
    if (this->addressFileStream.is_open()){
        while (std::getline(this->addressFileStream, addressLine)){
            std::string processedAddress = addressLine.substr(1,4);
            uint16_t parsedAddress = hex2doublebyte(processedAddress);
            this->addressesToExamine.insert(this->addressesToExamine.end(), parsedAddress);
        }
    }else{
        std::cout << "Unable to open file" << std::endl;
    }
}

std::string recordDataRepr(std::vector<uint8_t> recordData){
    std::string recordDataString = "";

    unsigned int dataIdx = 0;
    for (uint8_t recordDataElem : recordData){
        recordDataString.append(byte2hex(recordDataElem));

        if (dataIdx + 1 < recordData.size()){
            recordDataString.append(", ");
        }   

        dataIdx++;
    }

    return recordDataString;
}

void SRecord::printRecord(){
    std::cout << "Record Type: " << SRecordTypeStringMap.at(this->recordType) << std::endl;
    std::cout << "Record Size: " << (int)this->recordSize << std::endl;
    std::cout << "Record Address: " << byte2doublehex(this->recordStartingAddress) << std::endl;
    std::cout << "Record Data: " << recordDataRepr(this->recordData) << std::endl;
    std::cout << "Record Checksum: " << byte2hex(this->checkSum) << std::endl;
}

SRecord parseSRecordString(std::string rawSRecord){

    SRecord newRecord;

    std::string recordTypeString {
        rawSRecord[0],
        rawSRecord[1]
    };
    newRecord.recordType = parseStringToRecordType(recordTypeString);

    std::string byteCountString {
        rawSRecord[2], 
        rawSRecord[3]
    };
    
    newRecord.recordSize = hex2byte(byteCountString);
    unsigned int recordDataLeft = newRecord.recordSize;
   
    std::string addressString {
        rawSRecord[4], 
        rawSRecord[5], 
        rawSRecord[6], 
        rawSRecord[7]
    };
    newRecord.recordStartingAddress = hex2doublebyte(addressString);

    recordDataLeft -= 2; //remove the 2 starting address bytes
   
    unsigned int recordReadIdx = 8;
    while (recordDataLeft > 1){
        //read the data byte
        std::string dataByteHex {
            rawSRecord[recordReadIdx], 
            rawSRecord[recordReadIdx+1]
        };

        uint8_t dataByte = hex2byte(dataByteHex);

        //push the data byte
        newRecord.recordData.insert(newRecord.recordData.end(), dataByte);

        //Increment
        recordReadIdx+=2;
        recordDataLeft -= 1;
    }

    //read the checksum
    std::string checkSumString {rawSRecord[recordReadIdx], rawSRecord[recordReadIdx+1]};
    newRecord.checkSum = hex2byte(checkSumString);

    return newRecord;
}

SRecordType parseStringToRecordType(std::string rawSRecordType){
    if (rawSRecordType == "S0"){
        return SRecordType::Header;
    }
    else if (rawSRecordType == "S1"){
        return SRecordType::Data16;
    }
    else if (rawSRecordType == "S2"){
        return SRecordType::Data24;
    }
    else if (rawSRecordType == "S3"){
        return SRecordType::Data32;
    }
    else if (rawSRecordType == "S4"){
        return SRecordType::Reserved;
    }
    else if (rawSRecordType == "S5"){
        return SRecordType::Count16;
    }
    else if (rawSRecordType == "S6"){
        return SRecordType::Count24;
    }
    else if (rawSRecordType == "S7"){
        return SRecordType::StartAddress32;
    }
    else if (rawSRecordType == "S8"){
        return SRecordType::StartAddress24;
    }
    else if (rawSRecordType == "S9"){
        return SRecordType::StartAddress16;
    }
    else {
        return SRecordType::Unknown;
    }
}