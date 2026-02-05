// Struct for storing full WAZA data and methods for reading it

#pragma once

#include "data/Constants.h"

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

struct WazaFile
{
    std::string filePath;
    std::vector<uint8_t> data;
    std::unordered_map<uint16_t, std::array<char, kMoveNameLength>> moveNames;
};

void LoadWaza(WazaFile& waza);

std::unordered_map <uint16_t, std::array<char, kMoveNameLength>> ParseWaza(
    const std::vector<uint8_t>& wazaData);