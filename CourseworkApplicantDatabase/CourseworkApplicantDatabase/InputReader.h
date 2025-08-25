#ifndef INPUT_READER
#define INPUT_READER

#include <iostream>

class InputReader {
public:
	static int readInt(const std::string& prompt);
	static bool readBool(const std::string& prompt);
	static std::string readString(const std::string& prompt);
};

#endif
