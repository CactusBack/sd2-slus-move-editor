// UI widget for displaying move entries as a table

#pragma once

#include "data/MoveEntry.h"
#include "data/WazaFile.h"

#include <cstddef>
#include <cstdint>
#include <vector>

struct MoveTableContext
{
    std::vector<MoveEntry>& moveEntries;
    uint16_t& moveCount;
    size_t moveCapacity;
};

void DrawMoveTable(MoveTableContext context, const WazaFile& waza);