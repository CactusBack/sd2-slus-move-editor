// General-purpose utils for reading/writing/transforming binary data

#pragma once

#include "data/Constants.h"

#include <array>
#include <cstdint>
#include <string>
#include <vector>

uint8_t CharToNibble(char c);

std::string BytesToString(
	const std::array<uint8_t, kMoveEntryLength>& bytes);

uint16_t ReadU16LE(
	const std::vector<uint8_t>& data,
	const size_t offset);

void WriteU16LE(
	std::vector<uint8_t>& data,
	const size_t offset,
	const uint16_t value);

std::vector<uint8_t> LoadFile(
	const std::string& path);

void SaveFile(
    const std::string& path,
    const std::vector<uint8_t>& fileData);