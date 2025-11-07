#include "ConsolePrinter.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <sstream>

#define NOMINMAX
#include <windows.h>


void ConsolePrinter::setColor(Color color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(color));
}

void ConsolePrinter::resetConsoleColor() {
	setColor(Color::Default);
}

void ConsolePrinter::printInputMessage(const std::string& message) {
	std::cout << message;
	ScopedColor scoped(Color::Input);
	std::cout << ": ";
}

void ConsolePrinter::printErrorMessage(const std::string& message) {
	ScopedColor scoped(Color::Error);
	std::cout << message << std::endl;
}

void ConsolePrinter::printWarningMessage(const std::string& message) {
	ScopedColor scoped(Color::Warning);
	std::cout << message << std::endl;
}

void ConsolePrinter::printSuccessMessage(const std::string& message) {
	ScopedColor scoped(Color::Success);
	std::cout << message << std::endl;
}

void ConsolePrinter::printInfoMessage(const std::string& message) {
	ScopedColor scoped(Color::Default);
	std::cout << message << std::endl;
}

ConsolePrinter::ScopedColor::ScopedColor(Color color) {
	ConsolePrinter::setColor(color);
}
ConsolePrinter::ScopedColor::~ScopedColor() {
	ConsolePrinter::resetConsoleColor();
}