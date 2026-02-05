#pragma once

#include <array>
#include <cstdint>

constexpr size_t kMoveEntryLength{ 0x0C };
constexpr size_t kWazaEntryLength{ 0x3E };
constexpr size_t kWazaEntryNameOffset{ 0x26 };
constexpr size_t kMoveNameLength{ 0x18 };
constexpr size_t kMoveCountOffsetOld{ 0x41C08 };
constexpr size_t kMoveCountOffsetNew{ 0x3454 };
constexpr size_t kMoveDataOffsetOld{ 0x773F4 };
constexpr size_t kMoveDataOffsetNew{ 0x7CBC0 };
constexpr size_t kNewMovesHackOffset{ 0x41C14 };
constexpr uint16_t kNewMovesHackValue{ 0x4B0C };

static const std::array<uint8_t, kMoveEntryLength> kMoveTablePadding =
{ 
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const char* kTypeLabels[16] =
{
    "Non-Submission (0)", "Non-Submission (1)", "Non-Submission (2)", "Non-Submission (3)",
    "Non-Submission (4)", "Non-Submission (5)", "Non-Submission (6)", "Non-Submission (7)",
    "Submission (8)", "Submission (9)", "Submission (A)", "Submission (B)",
    "Submission (C)", "Submission (D)", "Submission (E)", "Submission (F)",
};

struct CategoryOption
{
    uint8_t value;
    const char* label;
};

static const CategoryOption kCategoryOptions[] =
{
    { 0x0, "Powerful (0)" },
    { 0x1, "Speedy (1)" },
    { 0x2, "Technical (2)" },
    { 0x3, "Rough Neck (3)" },
    { 0x8, "Powerful (8)" },
    { 0x9, "Speedy (9)" },
    { 0xA, "Technical (A)" },
    { 0xB, "Rough Neck (B)" },
};

inline const char* CategoryLabel(uint8_t value)
{
    for (const auto& opt : kCategoryOptions)
    {
        if (opt.value == value)
            return opt.label;
    }
    return "Invalid";
}