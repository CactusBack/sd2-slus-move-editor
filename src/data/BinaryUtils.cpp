// General-purpose utils for reading/writing/transforming binary data

#include "data/BinaryUtils.h"

#include <format>
#include <fstream>
#include <iostream>

uint8_t CharToNibble(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

std::string BytesToString(
    const std::array<uint8_t, kMoveEntryLength>& bytes)
{
    std::string string;
    string.reserve(bytes.size() * 3 - 1);

    for (uint8_t x : bytes)
    {
        string += std::format("{:02X}", x);
        string += " ";
    }

    string.pop_back(); // Remove final space
    return string;
}

uint16_t ReadU16LE(
    const std::vector<uint8_t>& data,
    const size_t offset)
{
    if (offset + 1 >= data.size())
        return 0;

    return data[offset] | (data[offset + 1] << 8);
}

void WriteU16LE(
    std::vector<uint8_t>& data,
    const size_t offset,
    const uint16_t value)
{
    data[offset] = static_cast<uint8_t>(value & 0xFF);
    data[offset + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    return;
}

std::vector<uint8_t> LoadFile(
    const std::string& path)
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open file for reading\n";
        return {};
    }

    std::streamsize size = file.tellg();
    if (size <= 0) {
        std::cerr << "Invalid file size\n";
        return {};
    }

    std::vector<uint8_t> fileData(static_cast<size_t>(size));
    file.seekg(0, std::ios::beg);
    if (!file.read(reinterpret_cast<char*>(fileData.data()), size)) {
        std::cerr << "Failed to read file\n";
        return {};
    }

    return fileData;
}

void SaveFile(
    const std::string& path,
    const std::vector<uint8_t>& fileData)
{
    std::ofstream file(path, std::ios::binary | std::ios::trunc);

    if (!file) {
        std::cerr << "Failed to open file for writing\n";
        return;
    }

    if (!file.write(reinterpret_cast<const char*>(fileData.data()), fileData.size())) {
        std::cerr << "Failed to write file\n";
    }

    return;
}