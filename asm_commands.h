#include "6502_lib.h"
#include "hexlib/hex_lib.h"
#include <map>
#include <vector>

#define DECLARE_COMMAND(CMDNAME) void CMDNAME(CPU6502 * cpu, DataBus * dataBus, std::vector<uint8_t> dataParams, AddressingMode addressingMode);

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
    IMPLIED
};

typedef void (*OpCodeFunction)(CPU6502*, DataBus*, std::vector<uint8_t>, AddressingMode);

struct OpCodeInformation {
    OpCodeFunction opCodeToCall;
    std::string mnemonicName;
    AddressingMode addressingMode;
    uint8_t bytes;
    uint8_t cycles;
};

DECLARE_COMMAND(LDA);
DECLARE_COMMAND(LDX);
DECLARE_COMMAND(LDY);
DECLARE_COMMAND(STA);
DECLARE_COMMAND(STX);
DECLARE_COMMAND(STY);
DECLARE_COMMAND(NOOP);
DECLARE_COMMAND(BRK);
DECLARE_COMMAND(TAX);
DECLARE_COMMAND(TAY);
DECLARE_COMMAND(TXA);
DECLARE_COMMAND(TYA);

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
};

//
// STA -> Store A into Memory
// Implement variant of LDA that works with constant value instead of address

