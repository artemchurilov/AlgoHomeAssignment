#include <iostream>
#include <vector>
#include <cstdint>
#include "../include/decode.h"

std::string decodeAscii85(std::string input)
{
    std::string output;
    std::vector<uint8_t> bytes(input.begin(),input.end());
    size_t i = 0;
    const size_t inputSize = bytes.size();
    while (i < inputSize)
    {
        if (bytes[i]=='z')
        {
            output.insert(output.end(),4,0);
            i++;
            continue;
        }

        std::string part;
        size_t original_len = 0;
        while (part.size()<5 && i<inputSize)
        {
            char c = bytes[i];
            if (c == 'z')
            {
                break;   
            }
            if (c < '!' || c > 'u')
            {
                i++;
                continue;   
            }
            part += c;
            i++;
            original_len++;
        }

        if (part.size()<5)
        {
            part.append(5-part.size(), 'u');
        }

        uint32_t value = 0;
        for (char c : part)
        {
            value = value * 85 + (c-33);
        }

        std::vector<uint8_t> decode_bytes(4);
        decode_bytes[0] = (value >> 24) & 0xFF;
        decode_bytes[1] = (value >> 16) & 0xFF;
        decode_bytes[2] = (value >> 8) & 0xFF;
        decode_bytes[3] = (value) & 0xFF;

        if (original_len < 5)
        {
            output.insert(output.end(), decode_bytes.begin(), decode_bytes.begin()+original_len);
        }
        else
        {
            output.insert(output.end(), decode_bytes.begin(), decode_bytes.end());

        }
    }
    return output;
}