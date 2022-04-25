#include "asm_commands.h"

uint8_t getFlagBit(bool bit);

void DisplayFlags (Flags flags);

bool checkCarryFlag(uint16_t value){
    return value & 0xFF00;
}

bool checkNegativeFlag(uint16_t value){
    return (value & 0x0080);
}

bool checkZeroFlag(uint16_t value){
    return (value & 0x00FF) == 0;
}

bool checkUnsignedOverflow(uint16_t sum){
    return sum > 255;
}

bool checkSignedOverflow(int8_t sum, int8_t operA, int8_t operB){
    if (operA > 0 && (operB * -1) < 0 && sum < 0){
        return true;
    }else if (operA < 0 && (operB * -1) > 0 && sum > 0){
        return true;
    }

    return false;
}

uint16_t GrabRefinedAddress(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    if (addressingMode == AddressingMode::IMMEDIATE){
        return (uint16_t)(cpu->PC + 1);
    }else if (addressingMode == AddressingMode::ZERO_PAGE){
        return (uint16_t) dataParams.at(0);
    }else if (addressingMode == AddressingMode::RELATIVE){
        return (uint16_t) ( (cpu->PC) + (int16_t)dataParams.at(0));
    } else {  
        // Absolute addressing
        return (uint16_t)((dataParams.at(1) << 8) | (dataParams.at(0)));
    }
}

void LoadIntoRegister(uint8_t * registerToPopulate, CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    uint16_t effectiveAddress = GrabRefinedAddress(cpu, dataBus, dataParams, addressingMode);
    std::cout << "effective address: " << byte2doublehex(effectiveAddress) << std::endl;
    *registerToPopulate = dataBus->Read(effectiveAddress);
}

void SaveToMemory(uint8_t * registerToTransfer, CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode){
    uint8_t databusWriteValue = *registerToTransfer;
    uint16_t qualifiedAddress = GrabRefinedAddress(cpu, dataBus, dataParams, addressingMode);
    dataBus->Write(qualifiedAddress, databusWriteValue);
}

void CompareRegisterToMemory(uint8_t * registerToCompare, CPU6502 * cpu, DataBus * dataBus, uint16_t memAddress){
    uint8_t numberToCompare = dataBus->Read(memAddress);
    uint8_t registerOfInterest = *registerToCompare;

    uint16_t tempDiff = (uint16_t)registerOfInterest - (uint16_t)numberToCompare;

    cpu->flags.carry = registerOfInterest >= numberToCompare;
    cpu->flags.zero = checkZeroFlag(tempDiff);
    cpu->flags.negative = checkNegativeFlag(tempDiff);
}

COMMAND_IMPL(CMP){
    uint16_t absAddr = GrabRefinedAddress(cpu, dataBus, dataParams, addressingMode);
    CompareRegisterToMemory(&(cpu->A), cpu, dataBus, absAddr);
}

COMMAND_IMPL(CPX){
    uint16_t absAddr = GrabRefinedAddress(cpu, dataBus, dataParams, addressingMode);
    CompareRegisterToMemory(&(cpu->X), cpu, dataBus, absAddr);
}

COMMAND_IMPL(CPY){
    uint16_t absAddr = GrabRefinedAddress(cpu, dataBus, dataParams, addressingMode);
    CompareRegisterToMemory(&(cpu->Y), cpu, dataBus, absAddr);
}

COMMAND_IMPL(ADC){
    uint16_t absAddr = GrabRefinedAddress(cpu, dataBus, dataParams, addressingMode);
    uint8_t numberToAdd = dataBus->Read(absAddr);
    uint8_t carry = getFlagBit(cpu->flags.carry);

    uint16_t tempSum = (uint16_t)cpu->A + (uint16_t)numberToAdd + (uint16_t)carry; 
    
    cpu->flags.carry = checkCarryFlag((uint16_t)tempSum);
    cpu->flags.zero = checkZeroFlag((uint16_t)tempSum);
    cpu->flags.overflow = checkUnsignedOverflow((uint16_t)tempSum);
    cpu->flags.negative = checkNegativeFlag((uint16_t)tempSum);

    cpu->A = tempSum & 0x00FF;
}

COMMAND_IMPL(SBC){
    uint16_t absAddr = GrabRefinedAddress(cpu, dataBus, dataParams, addressingMode);
    uint8_t carry = getFlagBit(cpu->flags.carry);
    uint8_t subValue = (((uint16_t) dataBus->Read(absAddr)) ^ 0xFF);

    uint16_t tempSum = (uint16_t)cpu->A + (uint16_t)subValue + (uint16_t)carry; 

    cpu->flags.carry = checkCarryFlag((uint16_t)tempSum);
    cpu->flags.zero = checkZeroFlag((uint16_t)tempSum);
    cpu->flags.overflow = checkSignedOverflow((int8_t) tempSum, (int8_t)cpu->A, (int8_t)(subValue+carry));
    cpu->flags.negative = checkNegativeFlag((uint16_t)tempSum);

    cpu->A = tempSum & 0x00FF;
}

COMMAND_IMPL(INC){
    uint16_t qualifiedAddress = GrabRefinedAddress(cpu, dataBus, dataParams, addressingMode);
    uint8_t currentMemValue = dataBus->Read(qualifiedAddress);
    dataBus->Write(qualifiedAddress, currentMemValue + 1);
}

COMMAND_IMPL(INX){
    cpu->X = cpu->X + 1;
}

COMMAND_IMPL(INY){
    cpu->Y = cpu->Y + 1;
}

COMMAND_IMPL(DEC){
    uint16_t qualifiedAddress = GrabRefinedAddress(cpu, dataBus, dataParams, addressingMode);
    uint8_t currentMemValue = dataBus->Read(qualifiedAddress);
    dataBus->Write(qualifiedAddress, currentMemValue - 1);
}

COMMAND_IMPL(DEX){
    cpu->X = cpu->X - 1;
}

COMMAND_IMPL(DEY){
    cpu->Y = cpu->Y - 1;
}

COMMAND_IMPL(CLC){
    cpu->flags.carry = 0;
}

COMMAND_IMPL(CLV){
    cpu->flags.overflow = 0;
}

COMMAND_IMPL(SEC){
    cpu->flags.carry = 1;
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

COMMAND_IMPL(BRK){
    std::cout << "A: $" << byte2hex(cpu->A) << ", ";
    std::cout << "X: $" << byte2hex(cpu->X) << ", ";
    std::cout << "Y: $" << byte2hex(cpu->Y) << std::endl;

    std::cout << std::endl;
    DisplayFlags(cpu->flags);
    std::cout << std::endl;

    logMem(dataBus);

}

void branchOnFlagStatus( std::vector<bool *> flagsToCheck , bool flagSet, CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode) {
    uint16_t address = GrabRefinedAddress(cpu, dataBus, dataParams, addressingMode);
    bool jointFlagStatus = true;
    for (bool * flagReference : flagsToCheck){
        bool flagStatus = *flagReference;
        if (flagStatus == false){
            jointFlagStatus = false;
        }
    }

    if (jointFlagStatus == flagSet){    
        cpu->PC = address;
    }
}

COMMAND_IMPL(BCS){
    branchOnFlagStatus(std::vector<bool*> {&(cpu->flags.carry)}, true, cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(BCC){
    branchOnFlagStatus(std::vector<bool*> {&(cpu->flags.carry)}, false, cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(BMI){
    branchOnFlagStatus(std::vector<bool*> {&(cpu->flags.negative)}, true, cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(BPL){
    branchOnFlagStatus(std::vector<bool*> {&(cpu->flags.negative)}, false, cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(BVS){
    branchOnFlagStatus(std::vector<bool*> {&(cpu->flags.overflow)}, true, cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(BVC){
    branchOnFlagStatus(std::vector<bool*> {&(cpu->flags.overflow)}, false, cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(BEQ){
    branchOnFlagStatus(std::vector<bool*> {&(cpu->flags.carry), &(cpu->flags.zero)}, true, cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(BNE){
    branchOnFlagStatus(std::vector<bool*> {&(cpu->flags.carry), &(cpu->flags.zero)}, false, cpu, dataBus, dataParams, addressingMode);
}

COMMAND_IMPL(JMP){
    uint16_t address = GrabRefinedAddress(cpu, dataBus, dataParams, addressingMode);
    cpu->PC = address - 3;
}

COMMAND_IMPL(TXA){
    cpu->A = cpu->X;
}

COMMAND_IMPL(TAX){
    cpu->X = cpu->A;
}

COMMAND_IMPL(TYA){
    cpu->A = cpu->Y;
}

COMMAND_IMPL(TAY){
    cpu->Y = cpu->A;
}

COMMAND_IMPL(RTS){

}

uint8_t getFlagBit(bool bit){
    return bit ? 1 : 0;
}

void DisplayFlags (Flags flags){
    std::cout << "N V - B D I Z C" << std::endl;
    
    //Negative Flag
    std::cout << (int)getFlagBit(flags.negative);
    std::cout << " "; 
    
    //Overflow flag
    std::cout << (int)getFlagBit(flags.overflow);
    std::cout << " "; 
    
    //Placeholder flag
    std::cout << (int)getFlagBit(false);
    std::cout << " "; 
    
    //Break flag
    std::cout << (int)getFlagBit(flags.breakbit);
    std::cout << " "; 

    // Decimal flag
    std::cout << (int)getFlagBit(flags.binary_decimal);
    std::cout << " "; 
    
    //Interrupt flag
    std::cout << (int)getFlagBit(flags.interrupt);
    std::cout << " "; 
    
    // Zero flag
    std::cout << (int)getFlagBit(flags.zero);
    std::cout << " "; 
    
    //Carry flag
    std::cout << (int)getFlagBit(flags.carry);
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