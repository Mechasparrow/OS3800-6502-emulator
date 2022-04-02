#include "6502_lib.h"
#include <map>

//TODO: Add addressing mode ENUM

enum AddressingMode {
    ZERO_PAGE,
    IMMEDIATE
};

void LDA(CPU6502 * cpu, DataBus * dataBus, uint16_t address, AddressingMode addressingMode);

typedef void (*OpCodeFunction)(CPU6502*, DataBus*, uint16_t, AddressingMode);

//TODO: Add OpCode lookup table
std::map<std::string, std::pair<OpCodeFunction,AddressingMode>> OpCodeLookupTable = {
    {"A9", {LDA, AddressingMode::IMMEDIATE} }
};

//
// STA -> Store A into Memory
// Implement variant of LDA that works with constant value instead of address