#include "FileUtils.h"

#include <filesystem>
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <fstream>

bool FileUtils::exists(const std::string& path) {
    return std::filesystem::exists(path);
}

bool FileUtils::createDirectory(const std::string& path) {
    try {
        return std::filesystem::create_directories(path);
    }
    catch (...) {
        return false;
    }
}

bool FileUtils::remove(const std::string& path) {
    try {
        return std::filesystem::remove(path);
    }
    catch (...) {
        return false;
    }
}

bool FileUtils::isWritable(const std::string& path) {
    std::ofstream test(path, std::ios::app);
    return test.is_open();
}

std::string FileUtils::saveFileDialog(const std::string& defaultName, const std::string& filter) {
    char fileName[MAX_PATH];
    strcpy_s(fileName, defaultName.c_str());

    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = filter.c_str();
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrDefExt = "txt";
    ofn.lpstrTitle = "Save File As...";
    ofn.Flags = OFN_OVERWRITEPROMPT;

    if (GetSaveFileNameA(&ofn))
        return std::string(fileName);
    return "";
}

std::string FileUtils::openFileDialog(const std::string& filter) {
    char fileName[MAX_PATH] = "";
    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = filter.c_str();
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = "Open File...";
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileNameA(&ofn))
        return std::string(fileName);
    return "";
}

bool FileUtils::writeToFile(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    if (!file.is_open())
        return false;

    file << content;
    return true;
}