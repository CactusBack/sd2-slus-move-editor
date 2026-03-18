// UI widget for displaying move entries as a table

#include "data/Constants.h"
#include "ui/MoveTable.h"

#include <imgui.h>

#include <cctype> // std::tolower

void DrawMoveTable(MoveTableContext& context, const WazaFile& waza)
{
    UpdateMoveFilterIndices(context, waza);
    
    ImGuiTableFlags flags =
        ImGuiTableFlags_ScrollX |
        ImGuiTableFlags_ScrollY |
        ImGuiTableFlags_Resizable |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_SizingFixedFit;

    if (ImGui::BeginTable("Move Table", 13, flags))
    {
        // Table header
        ImGui::TableSetupColumn("Hex", ImGuiTableColumnFlags_WidthFixed, 410.0f);
        ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 55.0f);
        ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, 250.0f);
        ImGui::TableSetupColumn("Category", ImGuiTableColumnFlags_WidthFixed, 205.0f);
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 280.0f);
        ImGui::TableSetupColumn("Impact", ImGuiTableColumnFlags_WidthFixed, 75.0f);
        ImGui::TableSetupColumn("Head", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("Torso", ImGuiTableColumnFlags_WidthFixed, 70.0f);
        ImGui::TableSetupColumn("Arms", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("Legs", ImGuiTableColumnFlags_WidthFixed, 70.0f);
        ImGui::TableSetupColumn("Total", ImGuiTableColumnFlags_WidthFixed, 67.5f);
        ImGui::TableSetupColumn("##Add", ImGuiTableColumnFlags_WidthFixed, 65.0f);
        ImGui::TableSetupColumn("##Delete", ImGuiTableColumnFlags_WidthFixed, 100.0f);

        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableHeadersRow();

        // Table rows
        for (size_t i = 0; i < context.moveFilterIndices.size(); ++i)
        {
            size_t moveIndex = context.moveFilterIndices[i];
            MoveEntry& move = context.moveEntries[moveIndex];
            
            ImGui::PushID(static_cast<int>(i));
            ImGui::TableNextRow();

            // Column 1: Hex
            ImGui::TableSetColumnIndex(0);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputText("##Hex",
                move.hexEditBuffer.data(),
                move.hexEditBuffer.size(),
                ImGuiInputTextFlags_CharsHexadecimal);

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                move.ApplyHexEdit();
            }

            // Column 2: ID
            ImGui::TableSetColumnIndex(1);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputScalar("##ID",
                ImGuiDataType_U16,
                &move.id,
                NULL,
                NULL,
                "%04X");

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                move.SetId(move.id);
            }

            // Column 3: Type
            ImGui::TableSetColumnIndex(2);
            ImGui::SetNextItemWidth(-FLT_MIN);
            int typeValue = move.type;

            if (ImGui::Combo("##Type",
                &typeValue,
                kTypeLabels,
                IM_ARRAYSIZE(kTypeLabels)))
            {
                move.type = static_cast<uint8_t>(typeValue);
                move.SetType(move.type);
            }

            // Column 4: Category
            ImGui::TableSetColumnIndex(3);
            ImGui::SetNextItemWidth(-FLT_MIN);
            const char* preview = CategoryLabel(move.category);

            if (ImGui::BeginCombo("##Category", preview))
            {
                for (const auto& option : kCategoryOptions)
                {
                    bool selected = (move.category == option.value);

                    if (ImGui::Selectable(option.label, selected))
                    {
                        move.category = option.value;
                        move.SetCategory(move.category);
                    }

                    if (selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }

                }

                ImGui::EndCombo();
            }

            // Column 5: Name
            ImGui::TableSetColumnIndex(4);
            const char* name = "";
            auto it = waza.moveNames.find(move.id);

            if (it != waza.moveNames.end())
            {
                name = it->second.data();
            }

            ImGui::Text("%s", name);

            // Column 6: Impact
            ImGui::TableSetColumnIndex(5);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputScalar("##Impact",
                ImGuiDataType_U8,
                &move.impact,
                NULL,
                NULL,
                "%02X");

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                move.SetImpact(move.impact);
            }

            // Column 7: Head
            ImGui::TableSetColumnIndex(6);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputScalar("##Head",
                ImGuiDataType_U8,
                &move.head,
                NULL,
                NULL,
                "%02X");

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                move.SetHead(move.head);
            }

            // Column 8: Torso
            ImGui::TableSetColumnIndex(7);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputScalar("##Torso",
                ImGuiDataType_U8,
                &move.torso,
                NULL,
                NULL,
                "%02X");

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                move.SetTorso(move.torso);
            }

            // Column 9: Arms
            ImGui::TableSetColumnIndex(8);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputScalar("##Arms",
                ImGuiDataType_U8,
                &move.arms,
                NULL,
                NULL,
                "%02X");

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                move.SetArms(move.arms);
            }

            // Column 10: Legs
            ImGui::TableSetColumnIndex(9);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputScalar("##Legs",
                ImGuiDataType_U8,
                &move.legs,
                NULL,
                NULL,
                "%02X");

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                move.SetLegs(move.legs);
            }

            // Column 11: Total
            ImGui::TableSetColumnIndex(10);
            ImGui::Text("%02X", move.total);

            // Column 12: Add
            ImGui::TableSetColumnIndex(11);
            bool addDisabled = context.moveCount == context.moveCapacity;

            if (addDisabled)
            {
                ImGui::BeginDisabled();
            }

            if (ImGui::Button(" Add "))
            {
                MoveEntry NewEntry;
                context.moveEntries.insert(context.moveEntries.begin() + moveIndex + 1, NewEntry);
                ++context.moveCount;
            };

            if (addDisabled)
            {
                ImGui::EndDisabled();
            }

            // Column 13: Delete 
            ImGui::TableSetColumnIndex(12);

            if (ImGui::Button(" Delete "))
            {
                context.moveEntries.erase(context.moveEntries.begin() + moveIndex);
                --context.moveCount;
            };

            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}

void UpdateMoveFilterIndices(MoveTableContext& context, const WazaFile& waza)
{
    context.moveFilterIndices.clear();

    for (size_t i = 0; i < context.moveEntries.size(); i++)
    {
        auto it = waza.moveNames.find(context.moveEntries[i].id);
        std::string moveName;

        if (it != waza.moveNames.end())
        {
            moveName = it->second.data();
        }
        else
        {
            moveName = "";
        }

        if (MatchesFilter(moveName, context.moveFilterQuery))
        {
            context.moveFilterIndices.push_back(i);
        }
    }
}

bool MatchesFilter(const std::string& string, const std::string& query)
{
    if (query.empty())
    {
        return true;
    }

    std::string stringLower = StringToLower(string);
    std::string queryLower = StringToLower(query);

    return stringLower.find(queryLower) != std::string::npos;
}

std::string StringToLower(std::string string)
{
    for (char& c : string)
    {
        c = std::tolower(c);
    }

    return string;
}