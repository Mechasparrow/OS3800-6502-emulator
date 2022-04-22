#include <iostream>
#include <fstream>
#include <vector>

#include "program_loader/6502_loader.h"
#include "asm_commands.h"

void SetProgramEntryPoint(CPU6502 * cpu, uint16_t startingAddress);
void FetchExecuteLoop(CPU6502 * cpu, DataBus * databus, uint16_t stopAddress);
bool validFile(std::string fileName);
bool getInputFiles(int argc, char ** argv, std::string * assemblyfile, std::string * addressesToCheckFile);

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

    DataBus mainDataBus;
    CPU6502 mainCpu;

    Loader6502 * loader = new Loader6502 {assemblyFilePath};
    if (addressToCheckFilePath != ""){
        delete loader;
        loader = new Loader6502 {assemblyFilePath, addressToCheckFilePath};
    }

    uint16_t programEntryPoint = 0;
    if (loader->recordRead){
        programEntryPoint = loader->burn(&mainDataBus);
    }
    delete loader;

    SetProgramEntryPoint(&mainCpu, programEntryPoint);

    std::cout << "Beginning CPU execution" << std::endl;
    FetchExecuteLoop(&mainCpu, &mainDataBus, hex2doublebyte("D000"));

    return 0;
}


bool getInputFiles(int argc, char ** argv, std::string * assemblyfile, std::string * addressesToCheckFile){
    std::string assemblyFilePath;
    std::string addressesToCheckFilePath;
    bool goodToRun = false;

    if (argc <= 1){
        goodToRun = false;
    }else if (argc == 2){
        assemblyFilePath = std::string(argv[1]);
        bool assemblyFileExists = validFile(assemblyFilePath);

        if (assemblyFileExists){
            goodToRun = true;
            *assemblyfile = assemblyFilePath;
        }else{
            goodToRun = false;
        }

    }else if (argc >= 3){
        assemblyFilePath = std::string(argv[1]);
        addressesToCheckFilePath = std::string(argv[2]);

        bool assemblyFileExists = validFile(assemblyFilePath);
        bool addressesToCheckFileExists = validFile(assemblyFilePath);

        if (assemblyFileExists && addressesToCheckFileExists){
            goodToRun = true;
            *assemblyfile = assemblyFilePath;
            *addressesToCheckFile = addressesToCheckFilePath;
        }else{
            goodToRun = false;
        }
    }
    
    return goodToRun;    
}

bool validFile(std::string fileName){
    std::ifstream file;
    file.open(fileName);

    if (file){
        file.close();
        return true;
    }else{
        return false;
    }
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
