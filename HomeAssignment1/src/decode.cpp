#include <vector>
#include <string>
#include <stdexcept>
#include <istream>
#include <ostream>
#include <cstdint>
#include <cctype>
#include "../include/decode.h"
#include "../include/const.h"

void validate_decoded_bytes(const std::vector<uint8_t>& data) {
    for (uint8_t byte : data) {
        if (byte != '\n' && byte != '\r' && (byte < 0x20 || byte > 0x7E)) {
            throw std::runtime_error("Invalid character in decoded data: 0x" + 
                                    std::to_string(static_cast<int>(byte)));
        }
    }
}

std::vector<uint8_t> decode_block(const std::string& group, size_t original_size) {
    if (group.size() != DECODE_BLOCK) {
        throw std::runtime_error("Invalid group size");
    }

    uint64_t num = 0;
    for (char c : group) {
        if (c < '!' || c > 'u') {
            throw std::runtime_error("Invalid ASCII85 character: " + std::string(1, c));
        }
        num = num * 85 + static_cast<uint8_t>(c - 33);
    }

    if (num > 0xFFFFFFFFULL) {
        throw std::runtime_error("Value exceeds 32-bit limit");
    }

    uint32_t num32 = static_cast<uint32_t>(num);
    std::vector<uint8_t> decoded(4);
    decoded[0] = (num32 >> 24) & 0xFF;
    decoded[1] = (num32 >> 16) & 0xFF;
    decoded[2] = (num32 >> 8)  & 0xFF;
    decoded[3] =  num32        & 0xFF;

    if (original_size < DECODE_BLOCK) {
        size_t output_bytes = original_size - 1;
        decoded.resize(output_bytes);
    }

    validate_decoded_bytes(decoded);
    
    return decoded;
}

void decode(std::istream& in, std::ostream& out) {
    std::string group;
    char c;
    while (in.get(c)) {
        if (std::isspace(c)) continue;

        if (c == 'z') {
            if (!group.empty()) throw std::runtime_error("'z' in middle of group");
            std::vector<uint8_t> zeros(4, 0);
            validate_decoded_bytes(zeros);
            out.write(reinterpret_cast<const char*>(zeros.data()), 4);
            continue;
        }

        group += c;
        if (group.size() == DECODE_BLOCK) {
            auto decoded = decode_block(group, DECODE_BLOCK);
            out.write(reinterpret_cast<const char*>(decoded.data()), decoded.size());
            group.clear();
        }
    }

    if (!group.empty()) {
        if (group.size() == 1) throw std::runtime_error("Lonely character in group");
        
        size_t original_size = group.size();
        while (group.size() < DECODE_BLOCK) group += 'u';
        
        auto decoded = decode_block(group, original_size);
        out.write(reinterpret_cast<const char*>(decoded.data()), decoded.size());
    }
}