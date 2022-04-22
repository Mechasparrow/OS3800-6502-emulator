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

uint16_t GetZeroPageAddress(std::vector<uint8_t> dataParams){
    return (uint16_t) dataParams.at(0);
}

uint16_t GetAbsoluteAddress(std::vector<uint8_t> dataParams){
    return (uint16_t)((dataParams.at(1) << 8) | (dataParams.at(0)));
}


void SaveToMemory(uint8_t * registerToTransfer, CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    uint8_t databusWriteValue = *registerToTransfer;

    if (addressingMode == AddressingMode::ZERO_PAGE){
        uint16_t qualifiedAddress = GetZeroPageAddress(dataParams);
        dataBus->Write(qualifiedAddress, databusWriteValue);
    }else if (addressingMode == AddressingMode::ABSOLUTE){
        uint16_t qualifiedAddress = GetAbsoluteAddress(dataParams);
        std::cout << byte2doublehex(qualifiedAddress) << std::endl;
        dataBus->Write(qualifiedAddress, databusWriteValue);
    }
}

COMMAND_IMPL(LDA){
    LoadIntoRegister(&(cpu->A), cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(STA){
    SaveToMemory(&(cpu->A), cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(STX){
    SaveToMemory(&(cpu->X), cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(STY){
    SaveToMemory(&(cpu->Y), cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(LDX){
    LoadIntoRegister(&(cpu->X), cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(LDY){
    LoadIntoRegister(&(cpu->Y), cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(NOOP){}

void logMem(DataBus * dataBus){
    for (uint16_t address : dataBus->addressesToExamine){
        uint8_t value = dataBus->Read(address);
        std::cout << "$" << byte2doublehex(address) << ": " << byte2hex(value) << std::endl;
    }
}

char getFlagBit(bool bit){
    return bit ? '1' : '0';
}

void DisplayFlags (Flags flags){
    std::cout << "N V - B D I Z C" << std::endl;
    
    //Negative Flag
    std::cout << getFlagBit(flags.negative);
    std::cout << " "; 
    
    //Overflow flag
    std::cout << getFlagBit(flags.overflow);
    std::cout << " "; 
    
    //Placeholder flag
    std::cout << getFlagBit(false);
    std::cout << " "; 
    
    //Break flag
    std::cout << getFlagBit(flags.breakbit);
    std::cout << " "; 

    // Decimal flag
    std::cout << getFlagBit(flags.binary_decimal);
    std::cout << " "; 
    
    //Interrupt flag
    std::cout << getFlagBit(flags.interrupt);
    std::cout << " "; 
    
    // Zero flag
    std::cout << getFlagBit(flags.zero);
    std::cout << " "; 
    
    //Carry flag
    std::cout << getFlagBit(flags.carry);
    std::cout << " "; 
    
    std::cout << std::endl;
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

COMMAND_IMPL(BRK){
    std::cout << "A: $" << byte2hex(cpu->A) << ", ";
    std::cout << "X: $" << byte2hex(cpu->X) << ", ";
    std::cout << "Y: $" << byte2hex(cpu->Y) << std::endl;

    std::cout << std::endl;
    DisplayFlags(cpu->flags);
    std::cout << std::endl;

    logMem(dataBus);

}

COMMAND_IMPL(JMP){
    if (addressingMode == AddressingMode::ABSOLUTE){
        uint16_t address = GetAbsoluteAddress(dataParams);
        cpu->PC = address - 3;
    }
}

COMMAND_IMPL(RTS){
    
}