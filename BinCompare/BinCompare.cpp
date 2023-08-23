#include <iostream>
#include <fstream>
#include <iomanip>
#include "color.h"

void printHexFormatted(byte b1, byte b2) {
    std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(b1);
    std::cout << " : ";
    std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(b2);
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    //file1, file2, skipranges...
    if (argc < 2) {//TODO better arg checks
        std::cout << "Usage <file1> <file2> <skipranges...>" << std::endl;
        std::cout << "Example: <file1.bin> <file2,bin> <0x3907-0x4D97> <0x9136-0x9738>" << std::endl;
        return 1;
    }
    std::ifstream file1(argv[1], std::ios::binary);
    std::ifstream file2(argv[2], std::ios::binary);

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
    std::streampos address = 0;
    while (file1.read(&byte1, 1) && file2.read(&byte2, 1)) {
        if (byte1 != byte2) {
            std::cout << dye::yellow("Byte mismatch") << " @ 0x" << address << "\t";
            printHexFormatted(byte1, byte2);
        }
        address += 1;
    }
    file1.close();
    file2.close();

    return 0;
}
