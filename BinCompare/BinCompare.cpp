#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include "color.h"

void printHexFormatted(byte b1, byte b2) {
    std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(b1);
    std::cout << " : ";
    std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(b2);
    std::cout << std::endl;
}

std::vector<std::string> formatSkipList(char* arr[], int size) {
    std::vector<std::string> converted;
    for (int i = 0; i < size; ++i) {
        std::string arg(arr[i]);
        converted.push_back(arg);
    }
    std::vector<std::string> formatted;
    for (int i = 0; i < size; i++) {
        if (converted[i].substr(0, 2) == "0x") {
            int split = converted[i].find('-');
            formatted.push_back(converted[i].substr(2, split-2));
            formatted.push_back(converted[i].substr(split+3, converted[i].size()-(split+3)));
        }
    }
    return formatted;
}

int main(int argc, char* argv[])
{
    //file1, file2, skipranges...
    bool verbose = false;
    if (argc < 2) {//TODO better arg checks
        std::cout << "Usage <file1> <file2> <skipranges...>" << std::endl;
        std::cout << "Example: \"file1.bin\" \"file2.bin\" 0x3907-0x4D97 0x9136-0x9A38" << std::endl;
        return 1;
    }
    std::vector<std::string> fVector = formatSkipList(argv, argc);
    if (verbose) {
        for (size_t i = 0; i < fVector.size(); i += 2) {
            std::cout << fVector[i] << " : " << fVector[i + 1] << std::endl;
        }
    }
    std::ifstream file1(argv[1], std::ios::binary), file2(argv[2], std::ios::binary);

    //basic file checks
    if (!file1.is_open()) {
        std::cerr << "Error opening file1." << std::endl;
        return 1;
    }
    if (!file2.is_open()) {
        std::cerr << "Error opening file2." << std::endl;
        return 1;
    }

    char byte1, byte2; 
    while (file1.read(&byte1, 1) && file2.read(&byte2, 1)) {
        for (int i = 0; i < fVector.size(); i += 2) {
            if (file1.tellg().operator-(1) == std::stoi(fVector[i], nullptr, 16)) {
                std::cout << dye::aqua("[Skipping from ") << dye::aqua(fVector[i]) << dye::aqua(" to ") << dye::aqua(std::stoul(fVector[i + 1], nullptr, 16)) << dye::aqua("]") << std::endl;
                file1.seekg(std::stoul(fVector[i + 1], nullptr, 16) + 1);
                file2.seekg(std::stoul(fVector[i + 1], nullptr, 16) + 1);
                file1.read(&byte1, 1);
                file2.read(&byte2, 1);
            }
        }
        //get bytes again here before end of loop

        if (byte1 != byte2) {
            std::cout << dye::yellow("Byte mismatch") << " @ 0x" << file1.tellg().operator-(1) << "\t";
            printHexFormatted(byte1, byte2);
        }
    }
    file1.close();
    file2.close();

    return 0;
}
