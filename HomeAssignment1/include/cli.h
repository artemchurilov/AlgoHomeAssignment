#ifndef CLI_H
#define CLI_H

#include <string>
#include <stdexcept>

struct Config
{
    bool decode_mode = false;
    std::string input_file;
    std::string output_file;
};

Config parse_command_line(int argc, char* argv[]);

#endif