#ifndef DECODE_H
#define DECODE_H

#include <vector>
#include <iostream>
#include <cstdint>

std::vector<uint8_t> decode_block(const std::string& group);
void decode(std::istream& in, std::ostream& out);

#endif