#pragma once

#include <string>

class FileUtils {
public:
    static bool exists(const std::string& path);
    static bool createDirectory(const std::string& path);
    static bool remove(const std::string& path);
    static bool isWritable(const std::string& path);
    static std::string saveFileDialog(const std::string& defaultName, const std::string& filter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
    static std::string openFileDialog(const std::string& filter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
    static bool writeToFile(const std::string& path, const std::string& content);
};