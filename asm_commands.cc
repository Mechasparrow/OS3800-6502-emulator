#include "asm_commands.h"

void LDA(CPU6502 * cpu, DataBus * dataBus, uint16_t address, AddressingMode addressingMode){
    uint8_t databusReadValue = dataBus->Read(address);
    cpu->A = databusReadValue;
}