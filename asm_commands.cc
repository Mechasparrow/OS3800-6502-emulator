#include "asm_commands.h"

void LoadIntoRegister(uint8_t * registerToPopulate, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    uint8_t databusReadValue = 0;

    if (addressingMode == AddressingMode::IMMEDIATE){
        databusReadValue = dataParams.at(0);
    }else{
        uint16_t effectiveAddress = (dataParams.at(1) << 8) | (dataParams.at(0));
        databusReadValue = dataBus->Read(effectiveAddress);
    }

    *registerToPopulate = databusReadValue;
}

void LDA(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    LoadIntoRegister(&(cpu->A), dataBus, dataParams, addressingMode);
}

void LDX(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    LoadIntoRegister(&(cpu->X), dataBus, dataParams, addressingMode);
}

void LDY(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    LoadIntoRegister(&(cpu->Y), dataBus, dataParams, addressingMode);
}

void NOOP(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){

}