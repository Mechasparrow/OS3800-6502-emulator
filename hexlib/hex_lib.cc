#include "hex_lib.h"

using std::map;

map<char, int> getHexMap(){
    unsigned char HEX[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    map<char, int> hexMap;

    for (int i = 0; i < 16; i++){
        hexMap.insert(hexMap.begin(), std::pair<char, int> (HEX[i], i) );
    }

    return hexMap;
}

unsigned char hex2char(std::string hexstring) {
    unsigned char higherByte = toupper(hexstring[0]);
    unsigned char lowerByte = toupper(hexstring[1]);

    map<char,int> hexMap = getHexMap();

    unsigned char mappedLowerHexValue;
    unsigned char mappedHigherHexValue;

    try {
        mappedLowerHexValue = (unsigned char) hexMap.at(lowerByte);
        mappedHigherHexValue = (unsigned char) hexMap.at(higherByte);
    }catch (const std::exception& e){
        mappedLowerHexValue = (unsigned char) 0;
        mappedHigherHexValue = (unsigned char) 0;
    }

    return (mappedHigherHexValue << 4) | mappedLowerHexValue;
}

std::string char2hex(unsigned char hexChar) {
    std::string emptyString = "";
    return emptyString;
}