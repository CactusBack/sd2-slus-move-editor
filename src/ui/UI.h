// Struct for tracking UI settings and UI-related functions

#pragma once

struct UIState
{
    bool tabOld = true;
    bool tabNew = true;

    int fontSize = 24;
    bool fontUpdate = true;
};

void InitUI(UIState& uiState);
void UpdateFont(UIState& uiState);
void RegisterUISettings(UIState& uiState);