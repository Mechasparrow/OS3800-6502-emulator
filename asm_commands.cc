#include "asm_commands.h"

void LoadIntoRegister(uint8_t * registerToPopulate, CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    uint8_t databusReadValue = 0;

    if (addressingMode == AddressingMode::IMMEDIATE){
        databusReadValue = dataParams.at(0);
    }else{
        uint16_t effectiveAddress = (dataParams.at(1) << 8) | (dataParams.at(0));
        databusReadValue = dataBus->Read(effectiveAddress);
    }

    *registerToPopulate = databusReadValue;
}

void SaveToMemory(uint8_t * registerToTransfer, CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    uint8_t databusWriteValue = *registerToTransfer;

    if (addressingMode == AddressingMode::ZERO_PAGE){
        uint16_t qualifiedAddress = (uint16_t)dataParams.at(0);
        dataBus->Write(qualifiedAddress, databusWriteValue);
    }else if (addressingMode == AddressingMode::ABSOLUTE){
        uint16_t qualifiedAddress = (dataParams.at(1) << 8) | (dataParams.at(0));
        std::cout << byte2doublehex(qualifiedAddress) << std::endl;
        dataBus->Write(qualifiedAddress, databusWriteValue);
    }
}

void LDA(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    LoadIntoRegister(&(cpu->A), cpu, dataBus, dataParams, addressingMode);
}

void STA(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    SaveToMemory(&(cpu->A), cpu, dataBus, dataParams, addressingMode);
}

void STX(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    SaveToMemory(&(cpu->X), cpu, dataBus, dataParams, addressingMode);
}

void STY(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    SaveToMemory(&(cpu->Y), cpu, dataBus, dataParams, addressingMode);
}


void LDX(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    LoadIntoRegister(&(cpu->X), cpu, dataBus, dataParams, addressingMode);
}

void LDY(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    LoadIntoRegister(&(cpu->Y), cpu, dataBus, dataParams, addressingMode);
}

void NOOP(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){

}

void logMemRange(DataBus * dataBus, uint16_t start, uint16_t end){
    for (uint16_t address = start; address <= end; address++){
        uint8_t value = dataBus->Read(address);
        std::cout << byte2doublehex(address) << ": " << byte2hex(value) << std::endl;
    }
}

void logZeroPage(DataBus * dataBus){
    uint8_t addressIterX;
    uint8_t addressIterY;


    for (addressIterY = 0; addressIterY < 4; addressIterY++){
        for (addressIterX = 0; addressIterX < 4; addressIterX++) {
            uint16_t fullAddress = addressIterY << 8 | (uint16_t) addressIterX;

            std::cout << std::hex << byte2hex(dataBus->Read(fullAddress)) << std::dec << " ";
        }

        std::cout << std::endl;
    }
}

void BRK(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    std::cout << "Debug state values here: " << std::endl;

    std::cout << "A register: " << byte2hex(cpu->A) << std::endl;
    std::cout << "X register: " << byte2hex(cpu->X) << std::endl;
    std::cout << "Y register: " << byte2hex(cpu->Y) << std::endl;

    logMemRange(dataBus, hex2doublebyte("00F0"), hex2doublebyte("00F4"));

}

