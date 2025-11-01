#include "InputReader.h"

#include <iostream>
#include <limits>
#include <sstream>
#include <algorithm>
#define NOMINMAX
#include <windows.h>

int InputReader::readInt(const std::string& prompt) {
	return readValue<int>(prompt, [](int) { return true; }, "Invalid input. Please enter an integer.\n");
}

float InputReader::readFloat(const std::string& prompt) {
	return readValue<float>(prompt, [](float) { return true; }, "Invalid input. Please enter a floating-point number.\n");
}

bool InputReader::readBool(const std::string& prompt) {
	return readValue<int>(prompt,
		[](int val) { return val == 0 || val == 1; },
		"Invalid input. Please enter 1 for Yes or 0 for No.\n") == 1;
}

std::string InputReader::readString(const std::string& prompt) {
	printInputMessage(prompt);
	setColor(ConsoleColor::Input);
	std::string value;
	std::getline(std::cin, value);
	setColor(ConsoleColor::Default);
	return value;
}

float InputReader::readScore(const std::string& prompt) {
	return readValue<float>(prompt,
		[](float score) { return score >= 100.0f && score <= 200.0f; },
		"Invalid input. Please enter a score between 100 and 200.\n");
}

std::string InputReader::readPassportNumber(const std::string& prompt) {
	std::string passportNumber;
	while (true) {
		printInputMessage(prompt);
		setColor(ConsoleColor::Input);
		std::getline(std::cin, passportNumber);
		setColor(ConsoleColor::Default);

		if (passportNumber.length() == 9 && std::all_of(passportNumber.begin(), passportNumber.end(), ::isdigit)) {
			return passportNumber;
		}
		else {
			printErrorMessage("Invalid passport number. It should be exactly 9 digits.\n");
		}
	}
}

std::string InputReader::readFullName(const std::string& prompt) {
	std::string fullName;
	while (true) {
		printInputMessage(prompt);
		setColor(ConsoleColor::Input);
		std::getline(std::cin, fullName);
		setColor(ConsoleColor::Default);

		std::istringstream iss(fullName);
		std::string word;
		int wordCount = 0;
		while (iss >> word) ++wordCount;

		if (wordCount >= 2 && wordCount <= 3) {
			return fullName;
		}
		else {
			printErrorMessage("Invalid full name. Please enter at least a first and last name.\n");
		}
	}
}

void InputReader::setColor(ConsoleColor color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(color));
}

void InputReader::printErrorMessage(const std::string& message) {
	setColor(ConsoleColor::Error);
	std::cout << message;
	setColor(ConsoleColor::Default);
}

void InputReader::printInputMessage(const std::string& message) {
	std::cout << message;
	setColor(ConsoleColor::Input);
	std::cout << ": ";
	setColor(ConsoleColor::Default);
}

void InputReader::printSuccessMessage(const std::string& message) {
	setColor(ConsoleColor::Success);
	std::cout << message << std::endl;
	setColor(ConsoleColor::Default);
}