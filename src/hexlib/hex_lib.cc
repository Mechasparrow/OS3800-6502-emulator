#include "hex_lib.h"

uint8_t hex2byte(std::string hexstring) {
    unsigned char higherByte = toupper(hexstring[0]);
    unsigned char lowerByte = toupper(hexstring[1]);

    uint8_t mappedLowerHexValue;
    uint8_t mappedHigherHexValue;

    try {
        mappedLowerHexValue = hexToByteMap.at(lowerByte);
        mappedHigherHexValue = hexToByteMap.at(higherByte);
    }catch (const std::exception& e){
        mappedLowerHexValue = 0;
        mappedHigherHexValue = 0;
    }

    return (mappedHigherHexValue << 4) | mappedLowerHexValue;
}

std::string byte2hex(uint8_t byte) {
    uint8_t lowerBittle = byte & 0b00001111;
    uint8_t upperBittle = (byte >> 4) & 0b00001111;

    std::string returnedHex = "00";

    char lowerBittleHex, upperBittleHex;

    try {
        lowerBittleHex = byteToHexMap.at(lowerBittle);
        upperBittleHex = byteToHexMap.at(upperBittle);
    }catch (const std::exception& e){
        lowerBittleHex = '0';
        upperBittleHex = '0';
    }

    returnedHex[0] = upperBittleHex;
    returnedHex[1] = lowerBittleHex;

    return returnedHex;
}

std::string byte2doublehex(uint16_t doublebyte){
    uint8_t lowerByte = doublebyte & 0b0000000011111111;
    uint8_t upperByte = (doublebyte >> 8) & 0b0000000011111111;
    
    std::string hexStringOutput = "0000";
    std::string lowerByteString = byte2hex(lowerByte);
    std::string upperByteString = byte2hex(upperByte);

    hexStringOutput[0] = upperByteString[0];
    hexStringOutput[1] = upperByteString[1];
    hexStringOutput[2] = lowerByteString[0];
    hexStringOutput[3] = lowerByteString[1];
    
    return hexStringOutput;
}

uint16_t hex2doublebyte(std::string hexstring){
    std::string lowerHex = "00";
    lowerHex[0] = hexstring[2];
    lowerHex[1] = hexstring[3];

    std::string upperHex = "00";
    upperHex[0] = hexstring[0];
    upperHex[1] = hexstring[1];

    uint8_t upperByte = hex2byte(upperHex);
    uint8_t lowerByte = hex2byte(lowerHex);

    uint16_t doubleByte = ((upperByte << 8) & 0b1111111100000000) | (lowerByte & 0b0000000011111111);
    return doubleByte;
}

