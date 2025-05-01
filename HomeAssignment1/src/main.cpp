#include "../include/cli.h"
#include "../include/file_io.h"
#include "../include/encode.h"
#include "../include/decode.h"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        Config config = parse_command_line(argc, argv);
        IOStreams streams = setup_streams(config.input_file, config.output_file);
        
        if (config.decode_mode) {
            decode(*streams.in, *streams.out);
        } else {
            encode(*streams.in, *streams.out);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    std::cout<<std::endl;
    return 0;
}