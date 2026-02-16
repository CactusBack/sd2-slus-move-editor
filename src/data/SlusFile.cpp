// Struct for storing full SLUS data and methods for reading/writing it

#include "data/BinaryUtils.h"
#include "data/SlusFile.h"

#include <algorithm>
#include <iostream>

bool LoadSlus( // Returns true if new moves hack is applied
    SlusFile& slus,
    std::vector<MoveEntry>& moveEntriesOld,
    std::vector<MoveEntry>& moveEntriesNew)
{

    slus.data = LoadFile(slus.filePath);

    if (slus.data.empty())
        return false;

    // Old moves
    slus.moveCountOld = ReadU16LE(slus.data, kMoveCountOffsetOld) - 1; // -1 for dummy entry

    moveEntriesOld = ParseSlus(slus.data, slus.moveCountOld, kMoveDataOffsetOld);

    for (auto& entry : moveEntriesOld)
        entry.UpdateHexEditBuffer();

    // New moves
    uint16_t currentNewMovesHackValue = ReadU16LE(slus.data, kNewMovesHackOffset);

    if (currentNewMovesHackValue == kNewMovesHackValue)
    {
        slus.moveCapacityNew = (slus.data.size() - kMoveDataOffsetNew) / kMoveEntryLength - 1; // -1 for dummy entry
        slus.moveCountNew = ReadU16LE(slus.data, kMoveCountOffsetNew) - 1; // -1 for dummy entry

        moveEntriesNew = ParseSlus(slus.data, slus.moveCountNew, kMoveDataOffsetNew);

        for (auto& entry : moveEntriesNew)
            entry.UpdateHexEditBuffer();
        
        return true;
    }
    
    return false;
}

std::vector<MoveEntry> ParseSlus(
    const std::vector<uint8_t>& slusData,
    const size_t moveCount,
    size_t moveDataOffset)
{
    std::vector<MoveEntry> moveEntries;
    moveEntries.resize(moveCount);

    for (size_t i = 0; i < moveCount; i++, moveDataOffset += kMoveEntryLength)
    {
        if (moveDataOffset + kMoveEntryLength > slusData.size())
        {
            std::cerr << "SLUS move table out of bounds\n";
            break;
        }

        std::copy_n(slusData.begin() + moveDataOffset, kMoveEntryLength, moveEntries[i].hex.begin());
        moveEntries[i].DecodeHex();
        moveEntries[i].name.fill(0);
    }

    return moveEntries;
}

void UpdateSlus(
    std::vector<uint8_t>& slusData,
    const std::vector<MoveEntry>& moveEntries,
    const size_t moveCount,
    const size_t moveCapacity,
    const size_t moveCountOffset,
    size_t moveDataOffset)
{
    // Move entries
    for (size_t i = 0; i < moveCount; i++, moveDataOffset += kMoveEntryLength) 
    {
        std::copy_n(moveEntries[i].hex.begin(),
            kMoveEntryLength,
            slusData.begin() + moveDataOffset);
    }

    // Dummy entry for move table padding
    std::copy_n(kMoveTablePadding.begin(),
        kMoveEntryLength,
        slusData.begin() + moveDataOffset);
    moveDataOffset += kMoveEntryLength;

    // Padding to preserve SLUS size and offsets
    if (moveCount < moveCapacity) 
    {
        size_t remainingEntries = moveCapacity - moveCount;
        size_t remainingBytes = remainingEntries * kMoveEntryLength;

        auto begin = slusData.begin() + moveDataOffset;
        auto end = begin + remainingBytes;

        if (end <= slusData.end()) {
            std::fill(begin, end, 0x00);
        }
        else {
            std::cerr << "Padding exceeds SLUS size\n";
        }
    }

    // Update move count (+1 for dummy entry)
    uint16_t moveCountWithPadding = static_cast<uint16_t>(moveCount + 1);
    WriteU16LE(slusData, moveCountOffset, moveCountWithPadding);

    return;
}