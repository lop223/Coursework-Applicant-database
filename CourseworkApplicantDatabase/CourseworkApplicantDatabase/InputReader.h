#pragma once

#include <iostream>
#include <functional>
#include <string>

#include "ConsolePrinter.h"

class InputReader {
public:
	static int readInt(const std::string& prompt);
	static float readFloat(const std::string& prompt);
	static bool readBool(const std::string& prompt);

	static std::string readString(const std::string& prompt);
	static float readScore(const std::string& prompt);
	static std::string readPassportNumber(const std::string& prompt);
	static std::string readFullName(const std::string& prompt);

private:
    template<typename T>
    static T readValue(
        const std::string& prompt,
        std::function<bool(const T&)> validator,
        const std::string& errorMessage
    ) {
        T value;
        while (true) {
            ConsolePrinter::printInputMessage(prompt);

            {
                ConsolePrinter::ScopedColor scoped(ConsolePrinter::Color::Input);
                std::cin >> value;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (validator(value)) {
                return value;
            }
            else {
                ConsolePrinter::printErrorMessage(errorMessage + "\n");
            }
        }
    }
};