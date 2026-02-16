#pragma once

#include "data/MoveEntry.h"
#include "data/SlusFile.h"
#include "data/WazaFile.h"
#include "ui/UI.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void DrawMainWindow(
    GLFWwindow* window,
    UIState& uiState,
    SlusFile& slus,
    WazaFile& waza,
    std::vector<MoveEntry>& moveEntriesOld,
    std::vector<MoveEntry>& moveEntriesNew);