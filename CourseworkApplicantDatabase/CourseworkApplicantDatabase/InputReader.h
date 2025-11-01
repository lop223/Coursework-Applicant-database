#ifndef INPUT_READER
#define INPUT_READER

#include <iostream>
#include <functional>

class InputReader {
public:
	static int readInt(const std::string& prompt);
	static float readFloat(const std::string& prompt);
	static bool readBool(const std::string& prompt);
	static std::string readString(const std::string& prompt);
	static float readScore(const std::string& prompt);
	static std::string readPassportNumber(const std::string& prompt);
	static std::string readFullName(const std::string& prompt);

	static void printErrorMessage(const std::string& message);
	static void printInputMessage(const std::string& message);
	static void printSuccessMessage(const std::string& message);
private:
	enum class ConsoleColor { Default = 7, Error = 4, Success = 2, Input = 6 };

    static void setColor(ConsoleColor color);

    template<typename T>
    static T readValue(
        const std::string& prompt,
        std::function<bool(const T&)> validator,
        const std::string& errorMessage
    ) {
        T value;
        while (true) {
            printInputMessage(prompt);
            setColor(ConsoleColor::Input);

            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (validator(value)) {
                    setColor(ConsoleColor::Default);
                    return value;
                }
                else {
                    printErrorMessage(errorMessage);
                }
            }
            else {
                printErrorMessage("Invalid input type.\n");
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
};

#endif
