#include <iostream>
#include <vector>
#include <cstdint>
#include "../include/encode.h"

std::string encodeAscii85(std::string input)
{
    std::string output;
    std::vector<uint8_t> bytes(input.begin(),input.end());
    size_t i = 0;
    const size_t inputSize = bytes.size();
    while (i < inputSize)
    {
        int pad = 0;
        uint32_t part = 0;
        for (int j=0; j<4; j++)
        {
            if (i < inputSize)
            {
                part = (part << 8) | bytes[i];
                ++i;
            }
            else
            {
                part <<= 8;
                ++pad;
            }
            
        }
        if (pad == 0 && part == 0) {
            output += 'z';
            continue;
        }
        
        char chars[5];
        uint32_t temp = part;
        for (int k=4; k>=0 ;k--)
        {
            chars[k]= temp%85;
            temp /= 85;
        }

        for (int k = 0; k < 5; ++k)
        {
            chars[k]+=33;
        }
        if (pad > 0) {
            output.append(chars, chars + (5 - pad));
        } else {
            output.append(chars, chars + 5);
        }
    }
    return output;

}
