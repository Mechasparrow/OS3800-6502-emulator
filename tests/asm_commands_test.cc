#include <gtest/gtest.h>
#include "asm_commands.h"

TEST(LoadIntoARegister, BasicAssertions) {
   CPU6502 testCpu;
   DataBus db;

   for (int i = 0; i < 64 * 1000; i++){
       uint16_t memAddress = (uint16_t) i;
       int databusValue = rand() % 255;

       db.Write(memAddress, databusValue);

       LDA(&testCpu, &db, memAddress, AddressingMode::ZERO_PAGE);

       ASSERT_EQ(databusValue, testCpu.A);

   }

}