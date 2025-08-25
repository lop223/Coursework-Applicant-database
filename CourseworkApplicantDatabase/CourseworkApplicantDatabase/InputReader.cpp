#include "InputReader.h"

#include <iostream>
#include <limits>
#include <sstream>

int InputReader::readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        else {
            std::cout << "Invalid input. Please enter an integer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

bool InputReader::readBool(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && (value == 0 || value == 1)) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value == 1;
        }
        else {
            std::cout << "Invalid input. Enter 1 for Yes, 0 for No.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string InputReader::readString(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}