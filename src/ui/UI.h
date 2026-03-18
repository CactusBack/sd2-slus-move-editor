// Struct for tracking UI settings and UI-related functions

#pragma once

#include <string>

struct UIState
{
    bool tabOld = true;
    bool tabNew = true;

    int fontSize = 24;
    bool fontUpdate = true;

    std::string moveFilterQuery;
};

void InitUI(UIState& uiState);
void UpdateFont(UIState& uiState);
void RegisterUISettings(UIState& uiState);