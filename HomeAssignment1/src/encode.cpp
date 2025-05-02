#include <iostream>
#include <vector>
#include <cstdint>
#include <cctype>
#include <algorithm>

#include "../include/encode.h"
#include "../include/const.h"

std::string encode_block(const std::vector<uint8_t>& data, size_t original_bytes)
{
    uint32_t num = 0;
    for (size_t i = 0; i < 4; ++i)
    {
        num = (num << 8) | (i < original_bytes ? data[i] : 0);
    }

    if (num == 0 && original_bytes == 4) return "z";

    std::string encoded;
    for (int i = 0; i < 5; ++i)
    {
        encoded.push_back(num % 85 + 33);
        num /= 85;
    }
    std::reverse(encoded.begin(), encoded.end());

    size_t encoded_length = original_bytes + 1;
    return encoded.substr(0, encoded_length);
}

void encode(std::istream& in, std::ostream& out)
{
    std::vector<uint8_t> buffer;
    char c;

    while (in.get(c))
    {
        buffer.push_back(c);

        if (buffer.size() == ENCODE_BLOCK)
        {
            out << encode_block(buffer, ENCODE_BLOCK);
            buffer.clear();
        }
    }

    if (!buffer.empty())
    {
        auto encoded = encode_block(buffer, buffer.size());
        out << encoded;
    }
    out.flush();
}