// UI widget for displaying move entries as a table

#pragma once

#include "data/MoveEntry.h"
#include "data/WazaFile.h"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

struct MoveTableContext
{
    std::vector<MoveEntry>& moveEntries;
    uint16_t& moveCount;
    size_t moveCapacity;
    
    const std::string& moveFilterQuery;
    std::vector<size_t> moveFilterIndices;
};

void DrawMoveTable(MoveTableContext& context, const WazaFile& waza);

void UpdateMoveFilterIndices(MoveTableContext& context, const WazaFile& waza);

bool MatchesFilter(const std::string& name, const std::string& query);

std::string StringToLower(std::string string);