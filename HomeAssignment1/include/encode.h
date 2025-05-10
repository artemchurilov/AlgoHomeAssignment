#ifndef ENCODE_H
#define ENCODE_H

#include <vector>
#include <iostream>
#include <cstdint>

std::string encode_block(const std::vector<uint8_t>& data, size_t bytes);
void encode(std::istream& in, std::ostream& out);

#endif