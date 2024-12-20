﻿#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <string>

namespace ini {
    int GetInt(std::wstring filePath, std::wstring appName, std::wstring keyName);
    int GetInt(std::wstring filePath, std::wstring appName, std::wstring keyName, int iniVal);

    float GetFloat(std::wstring filePath, std::wstring appName, std::wstring keyName);
    float GetFloat(std::wstring filePath, std::wstring appName, std::wstring keyName, float iniVal);

    bool GetBool(std::wstring filePath, std::wstring appName, std::wstring keyName);

    std::string GetString(std::wstring filePath, std::wstring appName, std::wstring keyName);
    std::string GetString(std::wstring filePath, std::wstring appName, std::wstring keyName, std::string iniVal);
}