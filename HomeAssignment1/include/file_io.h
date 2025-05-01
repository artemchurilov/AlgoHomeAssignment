#ifndef FILE_IO_H
#define FILE_IO_H

#include <fstream>
#include <memory>
#include <stdexcept>

struct IOStreams {
    std::istream* in;
    std::ostream* out;
    std::unique_ptr<std::ifstream> fin;
    std::unique_ptr<std::ofstream> fout;
};

IOStreams setup_streams(const std::string& input_file, const std::string& output_file);

#endif