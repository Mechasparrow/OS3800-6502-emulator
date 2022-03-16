#include <gtest/gtest.h>
#include <iostream>
#include "hex_lib.h"



TEST(ConvertHexStringToChar, BasicAssertions) {
    unsigned char retChar = hex2char("0A");
    
    unsigned char HEX[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    for (unsigned int b = 0; b < 2; b++){
        for (unsigned int c = 0; c < 16; c++){
            for (unsigned int i = 0; i < 16; i++){
                unsigned char expectedHexValue = HEX[i];
                std::string hexString = "00";

                hexString[1] = HEX[i];
                hexString[0] = HEX[c];

                if (b == 1){
                    hexString[1] = tolower(hexString[1]);
                    hexString[0] = tolower(hexString[0]);
                }

                unsigned char expectedValue = (unsigned char)(16 * c + i);
                
                unsigned char retChar = hex2char(hexString);
                ASSERT_EQ(expectedValue, retChar);
            }
        }
    }
    
    

}