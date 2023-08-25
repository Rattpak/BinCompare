#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include "color.h"

void printHexFormatted(byte b1, byte b2) {
    std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(b1);
    std::cout << " : ";
    std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(b2);
    std::cout << std::endl;
}

std::vector<std::string> formatSkipList(char* arr[], int size) {
    std::vector<std::string> result;

    for (int i = 0; i < size; ++i) {
        std::string str(arr[i]);

        //check if string starts with 0x
        if (str.substr(0, 2) == "0x" && str.find('-') != std::string::npos) {
            size_t dashPos = str.find('-');
            std::string hex1 = str.substr(2, dashPos - 2);
            std::string hex2 = str.substr(dashPos + 1);

            //check for valid hexadecimal
            bool validHex = true;
            for (char c : hex1) {
                if (!isxdigit(c)) {
                    validHex = false;
                    break;
                }
            }
            for (char c : hex2) {
                if (!isxdigit(c)) {
                    validHex = false;
                    break;
                }
            }

            if (validHex) {
                result.push_back(hex1);
                result.push_back(hex2);
            }
            else {
                std::cout << "Invalid hexadecimal format: " << str << std::endl;
            }
        }
    }
    return result;
}

int main(int argc, char* argv[])
{
    //file1, file2, skipranges...
    if (argc < 2) {//TODO better arg checks
        std::cout << "Usage <file1> <file2> <skipranges...>" << std::endl;
        std::cout << "Example: \"file1.bin\" \"file2.bin\" 0x3907-0x4D97 0x9136-0x9738" << std::endl;
        return 1;
    }
    std::vector<std::string> fVector = formatSkipList(argv, argc);
    for (size_t i = 0; i < fVector.size(); ++i) {
        std::cout << "index " << i << ": " << fVector[i] << std::endl;
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
