#include "../include/shell.h"
#include <iostream>
#include "../include/decode.h"
#include "../include/encode.h"

std::string readMultilineInput(const std::string& delimiter)
{
    std::string input, line;
    while (getline(std::cin, line))
    {
        if (line == delimiter) break;
        input += line + "\n";
    }
    return input;
}

void runInteractiveShell()
{
    std::string command;

    while (true)
    {
        std::cout << "> ";
        getline(std::cin, command);

        if (command == "ascii85 exit"||command == "ascii85 quit")
        {
            break;
        }
        else if (command == "ascii85 -e")
        {
            std::cout << "Enter data (end with 'END'):\n";
            std::string data = readMultilineInput("END");
            std::string encoded = encodeAscii85(data);
            std::cout << "Encoded:\n" << encoded << "\n";
        }
        else if (command == "ascii85 -d")
        {
            std::cout << "Enter ascii85 data (end with 'END'):\n";
            std::string data = readMultilineInput("END");
            std::string decoded = decodeAscii85(data);
            std::cout << std::string(decoded.begin(), decoded.end()) << "\n";
        }
        else
        {
            std::cout << "Unknown command. Try again.\n";
        }
    }
}


