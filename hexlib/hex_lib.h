#include <iostream>
#include <map>

const std::map<uint8_t, char> byteToHexMap {
    {0,'0'},
    {1,'1'},
    {2,'2'},
    {3,'3'},
    {4,'4'},
    {5,'5'},
    {6,'6'},
    {7,'7'},
    {8,'8'},
    {9,'9'},
    {10, 'A'},
    {11,'B'},
    {12,'C'},
    {13,'D'},
    {14, 'E'},
    {15, 'F'}
};

const std::map<char, uint8_t> hexToByteMap {
    {'0',0},
    {'1',1},
    {'2',2},
    {'3',3},
    {'4',4},
    {'5',5},
    {'6',6},
    {'7',7},
    {'8',8},
    {'9',9},
    {'A',10},
    {'B',11},
    {'C',12},
    {'D',13},
    {'E',14},
    {'F',15}
};

uint8_t hex2byte(std::string hexstring);
uint16_t hex2doublebyte(std::string hexstring);

std::string byte2hex(uint8_t byte);
std::string byte2doublehex(uint16_t doublebyte);