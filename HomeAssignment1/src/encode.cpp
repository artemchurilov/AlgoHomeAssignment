#include <iostream>
#include <vector>
#include <cstdint>
#include "../include/encode.h"
#include "../include/const.h"

std::string encode_block(const std::vector<uint8_t>& data, size_t bytes) 
{
    uint32_t num = 0;
    for (size_t i = 0; i < 4; ++i) {
        num = (num << 8) | (i < bytes ? data[i] : 0);
    }

    if (num == 0 && bytes == 4) return "z";

    std::vector<char> encoded(5);
    for (int i = 4; i >= 0; --i) {
        encoded[i] = num % 85 + 33;
        num /= 85;
    }
    
    return std::string(encoded.begin(), encoded.begin() + (bytes + 1));
}

void encode(std::istream& in, std::ostream& out)
{
    std::vector<uint8_t> buffer(ENCODE_BLOCK);
    while (in.read(reinterpret_cast<char*>(buffer.data()), ENCODE_BLOCK) || in.gcount() > 0) {
        out << encode_block(buffer, in.gcount());
    }
}