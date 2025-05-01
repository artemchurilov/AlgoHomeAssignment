#include <vector>
#include <string>
#include <stdexcept>
#include <istream>
#include <ostream>
#include <cstdint>
#include <cctype>
#include "../include/decode.h"
#include "../include/const.h"

void validate_output_bytes(const std::vector<uint8_t>& data)
{
    for (uint8_t byte : data)
    {
        if (byte!=0x0 && byte != '\n' && byte != '\r' && (byte < 0x20 || byte > 0x7E))
        {
            throw std::runtime_error("Invalid character in output: 0x" + std::to_string(static_cast<int>(byte)));
        }
    }
}

std::vector<uint8_t> decode_block(const std::string& group, size_t original_chars)
{
    if (group.size() != 5) throw std::runtime_error("Internal error: Invalid group size");

    uint64_t num = 0;
    for (char c : group)
    {
        if (c < '!' || c > 'u')
        {
            throw std::runtime_error(std::string("Invalid input character: ") + c);
        }
        num = num * 85 + static_cast<uint8_t>(c - 33);
    }

    if (num > 0xFFFFFFFFULL) throw std::runtime_error("Value exceeds 32-bit limit");

    std::vector<uint8_t> decoded(4);
    decoded[0] = (num >> 24) & 0xFF;
    decoded[1] = (num >> 16) & 0xFF;
    decoded[2] = (num >> 8)  & 0xFF;
    decoded[3] =  num        & 0xFF;

    if (original_chars < 5)
    {
        if (original_chars == 1) throw std::runtime_error("Incomplete group");
        decoded.resize(original_chars - 1);
    }

    validate_output_bytes(decoded);
    return decoded;
}

void decode(std::istream& in, std::ostream& out)
{
    std::string group;
    char c;
    bool in_group = false;

    while (in.get(c))
    {
        if (std::isspace(c))
        {
            if (in_group)
            {
                if (group.size() < 2) throw std::runtime_error("Truncated group");

                try
                {
                    size_t original = group.size();
                    group.resize(5, 'u');
                    auto decoded = decode_block(group, original);
                    out.write(reinterpret_cast<const char*>(decoded.data()), decoded.size());
                }
                catch (...)
                {
                    group.clear();
                    throw;
                }

                group.clear();
                in_group = false;
            }
            continue;
        }

        if (c == 'z')
        {
            if (in_group || !group.empty()) throw std::runtime_error("'z' in middle of group");

            std::string zcheck(1, 'z');
            for (int i = 0; i < 4; ++i)
            {
                if (!in.get(c) || c != 'z') throw std::runtime_error("Invalid 'z' group");
                zcheck += c;
            }

            std::vector<uint8_t> zeros(4, 0);
            validate_output_bytes(zeros);
            out.write("\0\0\0\0", 4);
            continue;
        }

        in_group = true;
        group += c;

        if (group.size() == 5)
        {
            try
            {
                auto decoded = decode_block(group, 5);
                out.write(reinterpret_cast<const char*>(decoded.data()), 4);
            }
            catch (...)
            {
                group.clear();
                throw;
            }
            group.clear();
            in_group = false;
        }
    }

    if (!group.empty())
    {
        if (group.size() < 2) throw std::runtime_error("Truncated final group");
        size_t original = group.size();
        group.resize(5, 'u');
        auto decoded = decode_block(group, original);
        out.write(reinterpret_cast<const char*>(decoded.data()), decoded.size());
    }
}