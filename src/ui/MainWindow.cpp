#include "data/BinaryUtils.h"
#include "renderer/Renderer.h"
#include "ui/MainWindow.h"
#include "ui/MoveTable.h"

#include <imgui.h>

#include <algorithm>

void DrawMainWindow(
    GLFWwindow* window,
    UIState& uiState,
    SlusFile& slus,
    WazaFile& waza,
    std::vector<MoveEntry>& moveEntriesOld,
    std::vector<MoveEntry>& moveEntriesNew)
{
    // Window position and size
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)display_w, (float)display_h));
    
    // Main window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15.0f, 15.0f));
    ImGui::Begin("Main Window", nullptr,
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_AlwaysUseWindowPadding);

    // Tab checkboxes and font size input
    ImGui::BeginGroup();
    const float spacing{ 15.0f };

    // Button "Save File"
    if (ImGui::Button(" Save File "))
    {
        UpdateSlus(slus.data, moveEntriesOld,
            slus.moveCountOld, slus.moveCapacityOld,
            kMoveCountOffsetOld, kMoveDataOffsetOld);

        if (slus.moveCountNew)
        {
            UpdateSlus(slus.data, moveEntriesNew,
                slus.moveCountNew, slus.moveCapacityNew,
                kMoveCountOffsetNew, kMoveDataOffsetNew);
        }

        SaveFile(slus.filePath, slus.data);
    }

    // Button "Settings"
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::Button(" Settings "))
        ImGui::OpenPopup("Settings Popup");

    // Popup "Settings"
    ImVec2 buttonPos = ImGui::GetItemRectMin();
    ImVec2 buttonSize = ImGui::GetItemRectSize();
    ImGui::SetNextWindowPos(ImVec2(buttonPos.x, buttonPos.y + buttonSize.y + 14.0f));

    if (ImGui::BeginPopup("Settings Popup"))
    {
        // Input "Font Size"
        ImGui::SetNextItemWidth(130.0f);
        ImGui::InputInt("Font Size", &uiState.fontSize);
        uiState.fontSize = std::clamp(uiState.fontSize, 12, 32);

        if (ImGui::IsItemDeactivatedAfterEdit())
            uiState.fontUpdate = true;

        ImGui::EndPopup();
    }

    // Checkbox "Old"
    ImGui::SameLine(0.0f, spacing);
    ImGui::Checkbox("Old", &uiState.tabOld);

    // Checkbox "New"
    ImGui::SameLine(0.0f, spacing);

    if (!slus.moveCountNew)
    {
        ImGui::BeginDisabled();
    }

    ImGui::Checkbox("New", &uiState.tabNew);

    if (!slus.moveCountNew)
    {
        ImGui::EndDisabled();
    }

    ImGui::EndGroup();

    ImGui::Dummy(ImVec2(0.0f, 6.0f));
    ImGui::Separator();

    // Move data columns
    int columnCount = (uiState.tabOld ? 1 : 0) + (uiState.tabNew ? 1 : 0);

    if (columnCount)
    {
        ImGui::Columns(columnCount, nullptr, true);

        // Old moves column
        if (uiState.tabOld)
        {
            MoveTableContext contextOld{ moveEntriesOld, slus.moveCountOld, slus.moveCapacityOld };

            ImGui::Spacing();
            ImGui::Text("Move count: %d/%d", slus.moveCountOld, slus.moveCapacityOld);
            ImGui::Spacing();

            // Old moves table
            DrawMoveTable(contextOld, waza);
        }

        // New moves column
        if (uiState.tabNew)
        {
            ImGui::NextColumn();
            MoveTableContext contextNew{ moveEntriesNew, slus.moveCountNew, slus.moveCapacityNew };

            ImGui::Spacing();
            ImGui::Text("Move count: %d/%d", slus.moveCountNew, slus.moveCapacityNew);
            ImGui::Spacing();

            // New moves table
            DrawMoveTable(contextNew, waza);
        }
    }

    ImGui::PopStyleVar();
    ImGui::End();
}