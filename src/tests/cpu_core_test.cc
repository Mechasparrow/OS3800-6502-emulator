#include <gtest/gtest.h>
#include <iostream>
#include "6502_lib.h"

TEST(EnsureCPUInit, BasicAssertions) {
	CPU6502 newCpu;

	//Assert that new cpu has been initialized to correct values
	ASSERT_EQ(newCpu.PC, 0);
	ASSERT_EQ(newCpu.A, 0);
	ASSERT_EQ(newCpu.X, 0);
	ASSERT_EQ(newCpu.Y, 0);
	ASSERT_EQ(newCpu.SP, 0);

	ASSERT_EQ(newCpu.flags.binary_decimal, false);
	ASSERT_EQ(newCpu.flags.breakbit, false);
	ASSERT_EQ(newCpu.flags.carry, false);
	ASSERT_EQ(newCpu.flags.interrupt, false);
	ASSERT_EQ(newCpu.flags.negative, false);
	ASSERT_EQ(newCpu.flags.overflow, false);
	ASSERT_EQ(newCpu.flags.zero, false);
}

TEST(EnsureDatabuseInit, BasicAssertions){
	DataBus databus;

	//Ensure RAM
	ASSERT_EQ(sizeof(databus.RAM), 256 * 256);

	for (unsigned int i = 0; i < 256 *256;i++){
		ASSERT_EQ(databus.RAM[i], 0);
	}
}

TEST(EnsureDatabuseRead, BasicAssertions){
	DataBus databus;

	uint8_t dumbRam[256 * 256];

	for (unsigned int i = 0; i < 256 * 256; i++){
		dumbRam[i] = rand() % 100;
		databus.RAM[i] = dumbRam[i];
	}

	for (unsigned int i = 0; i < 256 * 256; i++){
		uint8_t readValue = databus.Read(i);
		ASSERT_EQ(dumbRam[i], readValue);
	}


}

TEST(EnsureDatabuseWrite, BasicAssertions){
	DataBus databus;

	for (unsigned int i = 0; i < 256 * 256; i++){
		databus.Write(i, 100);
		ASSERT_EQ(100, databus.RAM[i]);
	}


}
