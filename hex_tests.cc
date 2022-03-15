#include <gtest/gtest.h>
#include <iostream>
#include "hexlib/hex_lib.h"



TEST(ConvertHexStringToChar, BasicAssertions) {
    unsigned char retChar = hex2char("0A");
    
    unsigned char HEX[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    for (unsigned int i = 0; i < 16; i++){
        unsigned char expectedHexValue = HEX[i];
        std::string hexString = "00";
        hexString[1] = HEX[i];
        unsigned char retChar = hex2char(hexString);
        ASSERT_EQ((unsigned char) i, retChar);
    }

}
