// Struct for storing move data

#pragma once

#include "data/Constants.h"

#include <array>
#include <cstdint>
#include <string>

struct MoveEntry
{
    // Raw hex data
    std::array<uint8_t, kMoveEntryLength> hex{};

    // Parsed data
    uint16_t id{};
    uint8_t type{}, category{}, impact{}, head{}, torso{}, arms{}, legs{}, total{};

    // UI-only
    std::array<char, kMoveNameLength> name{};
    std::array<char, kMoveEntryLength * 3> hexEditBuffer{};

    MoveEntry();

    void DecodeHex();
    void EncodeHex();

    void UpdateHexEditBuffer();
    void ApplyHexEdit();

    void SetId(uint16_t);
    void SetType(uint8_t);
    void SetCategory(uint8_t);
    void SetImpact(uint8_t);
    void SetHead(uint8_t);
    void SetTorso(uint8_t);
    void SetArms(uint8_t);
    void SetLegs(uint8_t);
};