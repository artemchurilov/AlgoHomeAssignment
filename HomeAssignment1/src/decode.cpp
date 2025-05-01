#include <iostream>
#include <vector>
#include <cstdint>
#include "../include/decode.h"
#include "../include/const.h"

std::vector<uint8_t> decode_block(const std::string& group)
{
    if (group == "z") return std::vector<uint8_t>(4, 0);

    uint32_t num = 0;
    for (char c : group)
    {
        if (c < '!' || c > 'u') throw std::runtime_error("Invalid character");
        num = num * 85 + (c - 33);
    }

    std::vector<uint8_t> decoded(4);
    for (size_t i = 0; i < 4; ++i)
    {
        decoded[i] = (num >> (24 - i * 8)) & 0xFF;
    }
    return decoded;
}

void decode(std::istream& in, std::ostream& out)
{
    std::string group;
    char c;
    while (in.get(c))
    {
        if (isspace(c)) continue;

        if (c == 'z')
        {
            if (!group.empty()) throw std::runtime_error("Invalid 'z' position");
            out.write("\0\0\0\0", 4);
            continue;
        }

        group += c;
        if (group.size() == DECODE_BLOCK)
        {
            auto decoded = decode_block(group);
            out.write(reinterpret_cast<char*>(decoded.data()), 4);
            group.clear();
        }
    }

    if (!group.empty())
    {
        if (group.size() < 2) throw std::runtime_error("Invalid padding");
        group.append(DECODE_BLOCK - group.size(), 'u');
        auto decoded = decode_block(group);
        out.write(reinterpret_cast<char*>(decoded.data()), group.size() - 1);
    }
}
