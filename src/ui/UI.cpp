// UI-related functions

#include "ui/UI.h"

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdio.h>

void InitUI(UIState& uiState)
{
    RegisterUISettings(uiState);
    ImGui::LoadIniSettingsFromDisk(ImGui::GetIO().IniFilename);
}

void UpdateFont(UIState& uiState)
{
    if (!uiState.fontUpdate)
        return;
    
    ImGuiIO& io = ImGui::GetIO();

    io.Fonts->Clear();

    ImFontConfig fontConfig;
    if (!io.Fonts->AddFontFromFileTTF(
        "assets/font/Inconsolata-Regular.ttf",
        static_cast<float>(uiState.fontSize),
        &fontConfig))
    {
        std::cerr << "Failed to load font\n";
    }

    io.Fonts->Build();

    // Required when updating at runtime
    ImGui_ImplOpenGL3_DestroyFontsTexture();
    ImGui_ImplOpenGL3_CreateFontsTexture();

    // Event to update UI
    glfwPostEmptyEvent();

    uiState.fontUpdate = false;
}

// ===================================================
// ImGui .ini handler for custom UI settings
// (currently only font size)
//
// This registers a custom section in imgui.ini:
//
// [Settings][UI]
// FontSize=%i
//
// ImGui calls:
// - UISettingsReadOpen() when entering the section
// - UISettingsReadLine() for each line inside it
// - UISettingsWriteAll() when saving settings
//
// ImGui handlers do not allow user data so we store
// a global pointer to uiState during registration.
// ===================================================

static UIState* g_uiState = nullptr;

static constexpr const char* kUISection = "UI";

static void* SettingsUIReadOpen(ImGuiContext*, ImGuiSettingsHandler*, const char*);
static void  SettingsUIReadLine(ImGuiContext*, ImGuiSettingsHandler*, void*, const char*);
static void  SettingsUIWriteAll(ImGuiContext*, ImGuiSettingsHandler*, ImGuiTextBuffer*);

void RegisterUISettings(UIState& uiState)
{
    g_uiState = &uiState;

    static ImGuiSettingsHandler handler{};
    handler.TypeName = "Settings";
    handler.TypeHash = ImHashStr("Settings");
    handler.ReadOpenFn = SettingsUIReadOpen;
    handler.ReadLineFn = SettingsUIReadLine;
    handler.WriteAllFn = SettingsUIWriteAll;

    ImGui::AddSettingsHandler(&handler);
}

static void* SettingsUIReadOpen(ImGuiContext*, ImGuiSettingsHandler*, const char* name)
{
    if (std::strcmp(name, kUISection) == 0)
        return reinterpret_cast<void*>(1); // Any non-null ptr value tells ImGui this section is handled

    return nullptr;
}

static void SettingsUIReadLine(ImGuiContext*, ImGuiSettingsHandler*, void*, const char* line)
{
    int size{ 0 };

    if (sscanf_s(line, "FontSize=%i", &size) == 1)
    {
        if (g_uiState)
            g_uiState->fontSize = std::clamp(size, 12, 32);
    }
}

static void SettingsUIWriteAll(ImGuiContext*, ImGuiSettingsHandler* handler, ImGuiTextBuffer* out_buf)
{
    if (!g_uiState)
        return;

    out_buf->appendf("[%s][%s]\n", handler->TypeName, kUISection);
    out_buf->appendf("FontSize=%d\n", g_uiState->fontSize);
    out_buf->append("\n");
}