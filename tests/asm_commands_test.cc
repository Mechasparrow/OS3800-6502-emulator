#include <gtest/gtest.h>
#include "asm_commands.h"

TEST(LoadIntoARegister, BasicAssertions) {
   CPU6502 testCpu;
   DataBus db;

   for (int i = 0; i < 2; i++){
       uint16_t memAddress = (uint16_t) i;
       uint8_t param1 = 0b0000000011111111 & memAddress;
       uint8_t param2 = (0b1111111100000000 & memAddress) >> 8;

       std::vector<uint8_t> params;
       params.insert(params.end(), param1);
       params.insert(params.end(), param2);

       int databusValue = rand() % 255;

       std::cout << std::hex << (int)params.at(0) << std::dec << "," << std::hex << (int)params.at(1) << std::dec << std::endl;

       db.Write(memAddress, databusValue);

       LDA(&testCpu, &db, params, AddressingMode::ABSOLUTE);

       ASSERT_EQ(databusValue, testCpu.A);

   }

}