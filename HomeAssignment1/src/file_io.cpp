#include "../include/file_io.h"
#include <iostream>

IOStreams setup_streams(const std::string& input_file,
                        const std::string& output_file)
{
    IOStreams streams;
    streams.in = &std::cin;
    streams.out = &std::cout;

    if (!input_file.empty())
    {
        streams.fin = std::make_unique<std::ifstream>(
                          input_file, std::ios::binary);
        if (!*streams.fin)
        {
            throw std::runtime_error("Can't open input file");
        }
        streams.in = streams.fin.get();
    }

    if (!output_file.empty())
    {
        streams.fout = std::make_unique<std::ofstream>(
                           output_file, std::ios::binary);
        if (!*streams.fout)
        {
            throw std::runtime_error("Can't create output file");
        }
        streams.out = streams.fout.get();

    }
    return streams;
}