#include <iostream>
#include <vector>

#include "program_loader/6502_loader.h"
#include "asm_commands.h"

void SetProgramEntryPoint(CPU6502 * cpu, uint16_t startingAddress);
void FetchExecuteLoop(CPU6502 * cpu, DataBus * databus, uint16_t stopAddress);

int main(){
    DataBus mainDataBus;
    CPU6502 mainCpu;

    uint16_t programEntryPoint = 0;
    

    Loader6502 loader {"../test_assembly/test.s19"};
    loader.readFileContents();
    if (loader.recordRead){
        programEntryPoint = loader.burnRecords(&mainDataBus);
    }

    SetProgramEntryPoint(&mainCpu, programEntryPoint);

    std::cout << "Beginning CPU execution" << std::endl;

    FetchExecuteLoop(&mainCpu, &mainDataBus, hex2doublebyte("D000"));

    return 0;
}

void SetProgramEntryPoint(CPU6502 * cpu, uint16_t startingAddress){
    cpu->PC = startingAddress;
}

void FetchExecuteLoop(CPU6502 * cpu, DataBus * databus, uint16_t stopAddress){
    while (cpu->PC != stopAddress){
        //fetch

        uint8_t currentInstruction = databus->Read(cpu->PC);

        OpCodeInformation opInformation = OpCodeLookupTable.at(byte2hex(currentInstruction));

        std::vector<uint8_t> dataParameters;
        if (opInformation.bytes - 1 > 0){
            int byteOffset = 1;
            while (opInformation.bytes - 1 - byteOffset >= 0){
                uint16_t paramAddress = cpu->PC + byteOffset;
                uint8_t paramData = databus->Read(paramAddress);
                dataParameters.insert(dataParameters.end(), paramData);
                byteOffset+=1;
            }
        }

        opInformation.opCodeToCall(cpu, databus, dataParameters, opInformation.addressingMode);

        //increment PC
        cpu->PC += opInformation.bytes;
    }
}
