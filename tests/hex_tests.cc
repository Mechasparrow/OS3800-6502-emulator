#include <gtest/gtest.h>
#include <iostream>
#include "hex_lib.h"

TEST(ConvertHexToDoubleByte, BasicAssertions){
    for (unsigned int i = 0; i < 256 * 256; i++){
        uint8_t lowerByte = i & 0b0000000011111111;
        uint8_t upperByte = (i >> 8) & 0b0000000011111111;
    
        std::string hexStringInput = "0000";
        std::string lowerByteString = byte2hex(lowerByte);
        std::string upperByteString = byte2hex(upperByte);

        hexStringInput[0] = upperByteString[0];
        hexStringInput[1] = upperByteString[1];
        hexStringInput[2] = lowerByteString[0];
        hexStringInput[3] = lowerByteString[1];

        uint16_t returnedDoubleByte = hex2doublebyte(hexStringInput);
        
        std::cout << "done testing " << hexStringInput << std::endl;
        ASSERT_EQ(i, returnedDoubleByte);
    }
}


TEST(ConvertDoubleByteToHex, BasicAssertions) {
    for (unsigned int i = 0; i < 256 * 256; i++){
        uint8_t lowerByte = i & 0b0000000011111111;
        uint8_t upperByte = (i >> 8) & 0b0000000011111111;
    
        std::string expectedHexString = "0000";


        std::string lowerByteString = byte2hex(lowerByte);
        std::string upperByteString = byte2hex(upperByte);

        expectedHexString[0] = upperByteString[0];
        expectedHexString[1] = upperByteString[1];
        expectedHexString[2] = lowerByteString[0];
        expectedHexString[3] = lowerByteString[1];

        std::string retHex = byte2doublehex(i);

        std::cout << "done testing " << expectedHexString << std::endl;
        ASSERT_EQ(expectedHexString, retHex);


    }
}


TEST(ConvertByteToHexString, BasicAssertions){
    unsigned char HEX[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    for (int i = 0; i < 255; i++){
        unsigned char expectedHexValue = HEX[i];
        std::string hexString = "00";

        uint8_t lowerBittle = i & 0b00001111;
        uint8_t upperBittle = (i >> 4) & 0b00001111;

        hexString[1] = HEX[lowerBittle];
        hexString[0] = HEX[upperBittle];

        std::cout << "Testing the following: " << i << ", Expecting: " << hexString << std::endl;
        std::string retHex = byte2hex(i);
        ASSERT_EQ(hexString, retHex);
    }
    
}


TEST(ConvertHexStringToChar, BasicAssertions) {
    unsigned char HEX[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    for (unsigned int b = 0; b < 2; b++){
        for (int i = 0; i < 255; i++){
            unsigned char expectedHexValue = HEX[i];
            std::string hexString = "00";

            uint8_t lowerBittle = i & 0b00001111;
            uint8_t upperBittle = (i >> 4) & 0b00001111;

            hexString[1] = HEX[lowerBittle];
            hexString[0] = HEX[upperBittle];

            if (b == 1){
                hexString[1] = tolower(hexString[1]);
                hexString[0] = tolower(hexString[0]);
            }

            uint8_t retChar = hex2byte(hexString);
            ASSERT_EQ(i, retChar);
        }
    }
    
    

}
