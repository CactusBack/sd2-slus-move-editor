// Struct for storing full SLUS data and methods for reading/writing it

#pragma once

#include "data/Constants.h"
#include "data/MoveEntry.h"

#include <cstdint>
#include <string>
#include <vector>

struct SlusFile
{
    std::string filePath;

    std::vector<uint8_t> data;

    uint16_t moveCountOld{ 0 };
    uint16_t moveCountNew{ 0 };
    
    static constexpr size_t moveCapacityOld{ 609 };
    size_t moveCapacityNew{ 0 };
};

bool LoadSlus(
    SlusFile& slus,
    std::vector<MoveEntry>& moveEntriesOld,
    std::vector<MoveEntry>& moveEntriesNew);

std::vector<MoveEntry> ParseSlus(
    const std::vector<uint8_t>& slusData,
    size_t moveCount,
    size_t moveDataOffset
);

void UpdateSlus(
    std::vector<uint8_t>& slusData,
    const std::vector<MoveEntry>& moveEntries,
    size_t moveCount,
    size_t moveCapacity,
    size_t moveCountOffset,
    size_t moveDataOffset
);