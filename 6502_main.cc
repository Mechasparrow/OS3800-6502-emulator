#include <iostream>

#include "program_loader/6502_loader.h"
#include "asm_commands.h"

int main(){
    DataBus mainDataBus;
    CPU6502 mainCpu;
    mainCpu.PC = hex2doublebyte("C000");

    Loader6502 loader {"../test_assembly/test.s19"};

    loader.readFileContents();
    
    if (loader.recordRead){
        loader.burnRecords(&mainDataBus);
    }

    std::cout << "Begining CPU execution" << std::endl;

    //fetch
    uint8_t currentInstruction = mainDataBus.Read(mainCpu.PC);
    OpCodeInformation opInformation = OpCodeLookupTable.at(byte2hex(currentInstruction));

    //execute
    std::cout << "Executing: " << opInformation.mnemonicName << std::endl;
    std::cout << "I will look at the next " << (int)(opInformation.bytes - 1) << " bytes as parameters." << std::endl;

    //increment PC

    //^ loop the 3 steps

    return 0;
}