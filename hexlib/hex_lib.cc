#include "hex_lib.h"

using std::map;

map<uint8_t, char> getByteToHexMap(){
    unsigned char HEX[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    map<uint8_t, char> hexMap;

    for (uint8_t i = 0; i < 16; i++){
        hexMap.insert(hexMap.begin(), std::pair<uint8_t, char> (i,HEX[i]) );
    }

    return hexMap;
}

map<char, uint8_t> getHexToByteMap(){
    unsigned char HEX[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    map<char, uint8_t> hexMap;

    for (uint8_t i = 0; i < 16; i++){
        hexMap.insert(hexMap.begin(), std::pair<char, uint8_t> (HEX[i], i) );
    }

    return hexMap;
}

uint8_t hex2byte(std::string hexstring) {
    unsigned char higherByte = toupper(hexstring[0]);
    unsigned char lowerByte = toupper(hexstring[1]);

    map<char,uint8_t> hexMap = getHexToByteMap();

    uint8_t mappedLowerHexValue;
    uint8_t mappedHigherHexValue;

    try {
        mappedLowerHexValue = hexMap.at(lowerByte);
        mappedHigherHexValue = hexMap.at(higherByte);
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

    map<uint8_t, char> byteToChar = getByteToHexMap();

    char lowerBittleHex, upperBittleHex;

    try {
        lowerBittleHex = byteToChar.at(lowerBittle);
        upperBittleHex = byteToChar.at(upperBittle);
    }catch (const std::exception& e){
        lowerBittleHex = '0';
        upperBittleHex = '0';
    }

    returnedHex[0] = upperBittleHex;
    returnedHex[1] = lowerBittleHex;

    return returnedHex;
}

std::string byte2doublehex(uint16_t doublebyte){
    return "";
}

uint16_t hex2doublebyte(std::string hexstring){
    return 0;
}

