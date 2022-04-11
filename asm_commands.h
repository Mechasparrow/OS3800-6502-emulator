#include "6502_lib.h"
#include <map>
#include <vector>

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

void LDA(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode);
void LDX(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode);
void LDY(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode);
void NOOP(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode);

typedef void (*OpCodeFunction)(CPU6502*, DataBus*, std::vector<uint8_t>, AddressingMode);

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
    {"00", {&NOOP, "NOOP", AddressingMode::ABSOLUTE, 1, 1}},
    {"A9", {&LDA, "LDA", AddressingMode::IMMEDIATE, 2, 2}},
    {"AD", {&LDA, "LDA", AddressingMode::ABSOLUTE, 3, 4}},
    {"A0", {&LDY, "LDY", AddressingMode::IMMEDIATE, 2, 2}},
    {"A2", {&LDX, "LDX", AddressingMode::IMMEDIATE, 2, 2}}
};

//
// STA -> Store A into Memory
// Implement variant of LDA that works with constant value instead of address

