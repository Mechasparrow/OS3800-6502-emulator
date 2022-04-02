#include "6502_lib.h"
#include <map>

//TODO: Add addressing mode ENUM

enum AddressingMode {
    ZERO_PAGE,
    ZERO_PAGE_X,
    IMMEDIATE,
    ABSOLUTE,
    ABSOLUTE_X,
    ABSOLUTE_Y,
    INDIRECT_X,
    INDIRECT_Y
};

void LDA(CPU6502 * cpu, DataBus * dataBus, uint16_t address, AddressingMode addressingMode);

typedef void (*OpCodeFunction)(CPU6502*, DataBus*, uint16_t, AddressingMode);

struct OpCodeInformation {
    OpCodeFunction opCodeToCall;
    std::string mnemonicName;
    AddressingMode addressingMode;
    uint8_t bytes;
    uint8_t cycles;
};

// Add OpCode lookup table
// {OpCode, {OpFunction, Mode, Bytes, Cycles}}
const std::map<std::string, OpCodeInformation> OpCodeLookupTable = {
    {"A9", {&LDA, "LDA", AddressingMode::IMMEDIATE, 2, 2}},
    {"AD", {&LDA, "LDA", AddressingMode::ABSOLUTE, 3, 4}}
};

//
// STA -> Store A into Memory
// Implement variant of LDA that works with constant value instead of address

