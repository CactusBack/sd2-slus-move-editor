// Struct for storing full WAZA data and methods for reading it

#include "data/BinaryUtils.h"
#include "data/WazaFile.h"

void LoadWaza(WazaFile& waza)
{
    waza.data = LoadFile(waza.filePath);
    waza.moveNames = ParseWaza(waza.data);
}

std::unordered_map <uint16_t, std::array<char, kMoveNameLength>> ParseWaza(const std::vector<uint8_t>& wazaData)
{
    std::unordered_map <uint16_t, std::array<char, kMoveNameLength>> moveNames;
    moveNames.reserve(wazaData.size() / kWazaEntryLength);

    for (size_t offset = 0; offset + kWazaEntryLength <= wazaData.size(); offset += kWazaEntryLength)
    {
        uint16_t id = ReadU16LE(wazaData, offset);
        std::array<char, kMoveNameLength> name = { 0 };
        std::copy_n(wazaData.begin() + offset + kWazaEntryNameOffset, kMoveNameLength, name.begin());
        moveNames.emplace(id, name);
    }

    return moveNames;
}