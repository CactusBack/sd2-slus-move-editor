// Struct for storing move data

#include "data/BinaryUtils.h"
#include "data/MoveEntry.h"

#include <algorithm>
#include <format>

MoveEntry::MoveEntry()
{
    DecodeHex();
    UpdateHexEditBuffer();
}

void MoveEntry::DecodeHex()
{
    id       = hex[0] | (hex[1] << 8);
    type     = hex[2] >> 4;
    category = hex[2] & 0x0F;
    impact   = hex[3];
    head     = ((hex[4] >> 4) | ((hex[5] & 0x0F) << 4)) / 4;
    torso    = ((hex[5] >> 4) | ((hex[6] & 0x0F) << 4)) & 0x3F;
    arms     = hex[6] / 4;
    legs     = hex[7] & 0x3F;
    total    = head + torso + arms + legs;
}

void MoveEntry::EncodeHex()
{
    // ID
    hex[0] = static_cast<uint8_t>(id & 0xFF);
    hex[1] = static_cast<uint8_t>((id >> 8) & 0xFF);

    // Type + Category
    hex[2] = static_cast<uint8_t>(((type & 0x0F) << 4) | (category & 0x0F));

    // Impact
    hex[3] = impact;

    // Head
    uint8_t headRaw = static_cast<uint8_t>(head * 4);
    hex[4] = (headRaw & 0x0F) << 4 | (hex[4] & 0x0F);
    hex[5] = (headRaw >> 4) & 0x0F | (hex[5] & 0xF0);

    // Torso + Arms
    uint8_t torsoRaw = static_cast<uint8_t>(torso);
    uint8_t armsRaw = static_cast<uint8_t>(arms * 4);
    hex[5] = (torsoRaw & 0x0F) << 4 | (hex[5] & 0x0F);
    hex[6] = ((torsoRaw >> 4) & 0x0F | (hex[6] & 0xF0)) | armsRaw;

    // Legs
    hex[7] = static_cast<uint8_t>(legs & 0x3F);

    // Recalculate total
    total = head + torso + arms + legs;

    // Update UI buffer
    UpdateHexEditBuffer();
}

void MoveEntry::UpdateHexEditBuffer()
{
    std::string string = BytesToString(hex);
    std::copy(string.begin(), string.end(), hexEditBuffer.begin());
    hexEditBuffer[string.size()] = 0x00;
}

void MoveEntry::ApplyHexEdit()
{
    std::array<uint8_t, kMoveEntryLength> newHex{};
    const char* ptr = hexEditBuffer.data();
    size_t byteIndex = 0;

    while (byteIndex < kMoveEntryLength)
    {
        while (*ptr == ' ') ++ptr; // Skip spaces

        if (!*ptr) break; // Remaining bytes are 0x00

        // Read hex byte
        char c1 = *ptr++;
        char c2 = *ptr ? *ptr++ : '0';  // If odd number of chars, pad with '0'
        newHex[byteIndex++] = (CharToNibble(c1) << 4) | CharToNibble(c2);
    }

    hex = newHex;
    DecodeHex();
    UpdateHexEditBuffer();
}

void MoveEntry::SetId(uint16_t newId)        { id = newId; EncodeHex(); }
void MoveEntry::SetType(uint8_t newType)     { type = newType; EncodeHex(); }
void MoveEntry::SetCategory(uint8_t newCat)  { category = newCat; EncodeHex(); }
void MoveEntry::SetImpact(uint8_t newImpact) { impact = newImpact; EncodeHex(); }
void MoveEntry::SetHead(uint8_t newHead)     { head = newHead; EncodeHex(); }
void MoveEntry::SetTorso(uint8_t newTorso)   { torso = newTorso; EncodeHex(); }
void MoveEntry::SetArms(uint8_t newArms)     { arms = newArms; EncodeHex(); }
void MoveEntry::SetLegs(uint8_t newLegs)     { legs = newLegs; EncodeHex(); }