#include "../include/encode.h"
#include <iostream>

int main()
{
    std::string text;
    std::getline(std::cin,text);
    std::cout << encodeAscii85(text)<<std::endl;
}