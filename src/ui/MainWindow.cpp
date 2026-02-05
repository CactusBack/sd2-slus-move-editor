#include "data/BinaryUtils.h"
#include "ui/MainWindow.h"
#include "ui/MoveTable.h"

#include <imgui.h>

void DrawMainWindow(
    GLFWwindow* window,
    AppState& appState,
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

    // Tab checkboxes
    if (ImGui::BeginTable("Tab Checkboxes", 3))
    {
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 175.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 100.0f);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 100.0f);
        ImGui::PushStyleColor(ImGuiCol_TableHeaderBg, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0, 0, 0, 0));
        ImGui::TableHeadersRow();
        ImGui::PopStyleColor(3);

        ImGui::TableSetColumnIndex(0);

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

        ImGui::TableSetColumnIndex(1);
        ImGui::Checkbox("Old", &appState.tabOld);

        ImGui::TableSetColumnIndex(2);

        if (!slus.moveCountNew)
        {
            ImGui::BeginDisabled();
        }

        ImGui::Checkbox("New", &appState.tabNew);

        if (!slus.moveCountNew)
        {
            ImGui::EndDisabled();
        }

        ImGui::EndTable();
        ImGui::Dummy(ImVec2(0.0f, 6.0f));
        ImGui::Separator();
    }

    // Move data columns
    int columnCount = (appState.tabOld ? 1 : 0) + (appState.tabNew ? 1 : 0);

    if (columnCount)
    {
        ImGui::Columns(columnCount, nullptr, true);

        // Old moves column
        if (appState.tabOld)
        {
            MoveTableContext contextOld{ moveEntriesOld, slus.moveCountOld, slus.moveCapacityOld };

            ImGui::Spacing();
            ImGui::Text("Move count: %d/%d", slus.moveCountOld, slus.moveCapacityOld);
            ImGui::Spacing();

            // Old moves table
            DrawMoveTable(contextOld, waza);
        }

        // New moves column
        if (appState.tabNew)
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