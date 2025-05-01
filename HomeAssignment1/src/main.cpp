#include "../include/encode.h"
#include "../include/decode.h"
#include <iostream>

int main()
{
    std::string text;
    std::getline(std::cin,text);
    std::cout << decodeAscii85(encodeAscii85(text))<<std::endl;
}