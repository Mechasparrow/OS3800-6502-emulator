#include <gtest/gtest.h>
#include <iostream>
#include "6502_lib.h"

TEST(EnsureCPUInit, BasicAssertions) {
	CPU6502 newCpu;

	//Assert that new cpu has been initialized to correct values
	ASSERT_EQ(newCpu.PC[0], (unsigned char)0);
	ASSERT_EQ(newCpu.PC[1], (unsigned char)0);	
	ASSERT_EQ(newCpu.A, (unsigned char)0);
	ASSERT_EQ(newCpu.X, (unsigned char)0);
	ASSERT_EQ(newCpu.Y, (unsigned char)0);
	ASSERT_EQ(newCpu.SP, (unsigned char)0);
	ASSERT_EQ(newCpu.flags, (unsigned char)0);
}

TEST(EnsureDatabuseInit, BasicAssertions){
	DataBus databus;

	//Ensure RAM
	ASSERT_EQ(sizeof(databus.RAM), 64 * 1000);

	for (unsigned int i = 0; i < 64 *1000;i++){
		ASSERT_EQ(databus.RAM[i], (unsigned char) 0);
	}
}
