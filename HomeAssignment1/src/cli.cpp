#include "../include/cli.h"
#include <cstring>
#include <iostream>

Config parse_command_line(int argc, char* argv[]) {
    Config config;
    
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-d") == 0) {
            config.decode_mode = true;
        }
        else if (std::strcmp(argv[i], "-o") == 0) {
            if (++i >= argc) {
                throw std::runtime_error("Missing output file after -o");
            }
            config.output_file = argv[i];
        }
        else if (config.input_file.empty()) {
            config.input_file = argv[i];
        }
        else {
            throw std::runtime_error("Invalid command line arguments");
        }
    }
    return config;
}