#include <iostream>
#include <fstream>
#include <vector>

#include "program_loader/6502_loader.h"
#include "input_validation.h"
#include "asm_commands.h"

void SetProgramEntryPoint(CPU6502 * cpu, uint16_t startingAddress);
void FetchExecuteLoop(CPU6502 * cpu, DataBus * databus, uint16_t stopAddress);
void setupCPU(CPU6502 * cpu, DataBus * databus, std::string assemblyFilePath, std::string addressToCheckFilePath);

int main(int argc, char ** argv){
    std::string assemblyFilePath = "";
    std::string addressToCheckFilePath = "";

    bool validatedInputs = getInputFiles(argc, argv, &assemblyFilePath, &addressToCheckFilePath);

    if (!validatedInputs){
        std::cout << "Please pass in the s19 file like the following" << std::endl;
        std::cout << "./6502_emulator test.s19" << std::endl;
        std::cout << "Make sure the path to your file is correct as well" << std::endl;
        return -1;  
    }

    DataBus * mainDataBus = new DataBus;
    CPU6502 * mainCpu = new CPU6502;

    setupCPU(mainCpu, mainDataBus, assemblyFilePath, addressToCheckFilePath);

    std::cout << "Beginning CPU execution" << std::endl;
    FetchExecuteLoop(mainCpu, mainDataBus, hex2doublebyte("FFFF"));

    delete mainCpu;
    delete mainDataBus;
    return 0;
}

void setupCPU(CPU6502 * cpu, DataBus * databus, std::string assemblyFilePath, std::string addressToCheckFilePath){
    Loader6502 * loader = new Loader6502 {assemblyFilePath};
    if (addressToCheckFilePath != ""){
        delete loader;
        loader = new Loader6502 {assemblyFilePath, addressToCheckFilePath};
    }

    uint16_t programEntryPoint = 0;
    if (loader->recordRead){
        programEntryPoint = loader->burn(databus);
    }
    delete loader;

    SetProgramEntryPoint(cpu, programEntryPoint);
}

void SetProgramEntryPoint(CPU6502 * cpu, uint16_t startingAddress){
    cpu->PC = startingAddress;
}

std::vector<uint8_t> parseDataParameters(CPU6502 * cpu, DataBus * databus, OpCodeInformation opInformation){
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
    return dataParameters;
}

void LogCommand(OpCodeInformation opInformation){
    std::cout << "Running: " << opInformation.mnemonicName << std::endl;
}

void LogAddress(uint16_t address){
    std::cout << "Address: " << byte2doublehex(address) << std::endl;
}

void FetchExecuteLoop(CPU6502 * cpu, DataBus * databus, uint16_t stopAddress){
    while (cpu->PC != stopAddress){
        //fetch
        uint8_t currentInstruction = databus->Read(cpu->PC);

        //Execute
        OpCodeInformation opInformation = OpCodeLookupTable.at(byte2hex(currentInstruction));
        std::vector<uint8_t> dataParameters = parseDataParameters(cpu, databus, opInformation);
        
        if (opInformation.mnemonicName != "NOP" && opInformation.mnemonicName != "RTS"){
            LogCommand(opInformation);
        }else if (opInformation.mnemonicName == "RTS"){
            break;
        }
        
        opInformation.opCodeToCall(cpu, databus, dataParameters, opInformation.addressingMode);

        //Increment
        cpu->PC += opInformation.bytes;
    }
}
