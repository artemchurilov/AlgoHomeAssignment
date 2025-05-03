#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <sstream>
#include <string>

std::vector<uint8_t> decode_block(const std::string& block)
{
    if (block.size() != 5)
    {
        throw std::invalid_argument("Block must be exactly 5 characters long");
    }

    uint32_t num = 0;
    for (char c : block)
    {
        if (c < 33 || c > 117)
        {
            throw std::invalid_argument("Invalid character in ASCII85 block");
        }
        uint8_t value = c - 33;
        num = num * 85 + value;
    }

    std::vector<uint8_t> result(4);
    result[0] = (num >> 24) & 0xFF;
    result[1] = (num >> 16) & 0xFF;
    result[2] = (num >> 8)  & 0xFF;
    result[3] =  num        & 0xFF;

    return result;
}

void decode(std::istream& in, std::ostream& out)
{
    std::string filtered;
    char c;

    while (in.get(c))
    {
        if (c >= 33 && c <= 117)
        {
            filtered += c;
        }
    }

    const size_t block_size = 5;
    const size_t total_len = filtered.size();
    size_t remainder = total_len % block_size;

    if (remainder == 1)
    {
        throw std::runtime_error("Invalid last block size (1 character)");
    }

    for (size_t i = 0; i < total_len - remainder; i += block_size)
    {
        std::string block = filtered.substr(i, block_size);
        auto decoded = decode_block(block);
        out.write(reinterpret_cast<char*>(decoded.data()), decoded.size());
    }

    if (remainder > 0)
    {
        std::string last_block = filtered.substr(total_len - remainder, remainder);
        last_block.append(block_size - remainder, 'u');
        auto decoded = decode_block(last_block);
        out.write(reinterpret_cast<char*>(decoded.data()), remainder - 1);
    }
}