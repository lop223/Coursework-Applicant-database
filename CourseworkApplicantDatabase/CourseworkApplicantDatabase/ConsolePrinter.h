#pragma once

#include<string>

class ConsolePrinter final {
public:
    enum class Color { Default = 7, Error = 4, Success = 2, Input = 6, Warning = 6 };

    static void printErrorMessage(const std::string& message);
    static void printWarningMessage(const std::string& message);
    static void printSuccessMessage(const std::string& message);
    static void printInputMessage(const std::string& message);
    static void printInfoMessage(const std::string& message);

    class ScopedColor {
    public:
        explicit ScopedColor(Color color);
        ~ScopedColor();
    };

private:
    static void setColor(Color color);

    static void resetConsoleColor();
};
