#include "6502_lib.h"
#include "hexlib/hex_lib.h"
#include <map>
#include <vector>

#define COMMAND_IMPL(CMDNAME) void CMDNAME(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode)

//TODO: Add addressing mode ENUM

enum AddressingMode {
    ZERO_PAGE,
    ZERO_PAGE_X,
    IMMEDIATE,
    ABSOLUTE,
    ABSOLUTE_X,
    ABSOLUTE_Y,
    INDIRECT_X,
    INDIRECT_Y,
    IMPLIED,
    INDIRECT
};

typedef void (*OpCodeFunction)(CPU6502*, DataBus*, std::vector<uint8_t>, AddressingMode);

struct OpCodeInformation {
    OpCodeFunction opCodeToCall;
    std::string mnemonicName;
    AddressingMode addressingMode;
    uint8_t bytes;
    uint8_t cycles;
};

COMMAND_IMPL(LDA);
COMMAND_IMPL(LDX);
COMMAND_IMPL(LDY);
COMMAND_IMPL(STA);
COMMAND_IMPL(STX);
COMMAND_IMPL(STY);
COMMAND_IMPL(NOOP);
COMMAND_IMPL(BRK);
COMMAND_IMPL(TAX);
COMMAND_IMPL(TAY);
COMMAND_IMPL(TXA);
COMMAND_IMPL(TYA);

/*
Register Instructions
Affect Flags: N Z

These instructions are implied mode, have a length of one byte and require two machine cycles.

MNEMONIC                 HEX
TAX (Transfer A to X)    $AA
TXA (Transfer X to A)    $8A
DEX (DEcrement X)        $CA
INX (INcrement X)        $E8
TAY (Transfer A to Y)    $A8
TYA (Transfer Y to A)    $98
DEY (DEcrement Y)        $88
INY (INcrement Y)        $C8
*/
COMMAND_IMPL(TAX);
COMMAND_IMPL(TXA);
COMMAND_IMPL(TAY);
COMMAND_IMPL(TYA);



/* Jump instructions */
COMMAND_IMPL(JMP);

/* Stack instructions */
COMMAND_IMPL(RTS);

// Add OpCode lookup table
// {OpCode, {OpFunction, Mode, Bytes, Cycles}}
const std::map<std::string, OpCodeInformation> OpCodeLookupTable = {
    {"EA", {&NOOP, "NOP", AddressingMode::IMPLIED, 1, 1}},
    {"A9", {&LDA, "LDA", AddressingMode::IMMEDIATE, 2, 2}},
    {"AD", {&LDA, "LDA", AddressingMode::ABSOLUTE, 3, 4}},
    {"A0", {&LDY, "LDY", AddressingMode::IMMEDIATE, 2, 2}},
    {"A2", {&LDX, "LDX", AddressingMode::IMMEDIATE, 2, 2}},
    {"00", {&BRK, "BRK", AddressingMode::IMPLIED, 1, 1}},
    {"85", {&STA, "STA", AddressingMode::ZERO_PAGE, 2, 3}},
    {"8D", {&STA, "STA", AddressingMode::ABSOLUTE, 3, 4}},
    {"86", {&STX, "STX", AddressingMode::ZERO_PAGE, 2, 3}},
    {"8E", {&STX, "STX", AddressingMode::ABSOLUTE, 3, 4}},
    {"84", {&STY, "STY", AddressingMode::ZERO_PAGE, 2, 3}},
    {"8C", {&STY, "STY", AddressingMode::ABSOLUTE, 3, 4}},
    {"4C", {&JMP, "JMP", AddressingMode::ABSOLUTE, 3, 3}},
    {"60", {&RTS, "RTS", AddressingMode::IMPLIED, 1, 6}},
    {"AA", {&TAX, "TAX", AddressingMode::IMPLIED, 1, 2}},
    {"8A", {&TXA, "TXA", AddressingMode::IMPLIED, 1, 2}},
    {"A8", {&TAY, "TAY", AddressingMode::IMPLIED, 1, 2}},
    {"98", {&TYA, "TYA", AddressingMode::IMPLIED, 1, 2}},
};

//
// STA -> Store A into Memory
// Implement variant of LDA that works with constant value instead of address

