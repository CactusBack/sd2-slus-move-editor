// UI widget for displaying move entries as a table

#include "data/Constants.h"
#include "ui/MoveTable.h"

#include <imgui.h>

void DrawMoveTable(MoveTableContext context, const WazaFile& waza)
{
    if (ImGui::BeginTable("Move Table", 13, ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | 
                                            ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg))
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
        for (size_t j = 0; j < context.moveEntries.size(); ++j)
        {
            ImGui::PushID(static_cast<int>(j));
            ImGui::TableNextRow();

            // Column 1: Hex
            ImGui::TableSetColumnIndex(0);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputText("##Hex",
                context.moveEntries[j].hexEditBuffer.data(),
                context.moveEntries[j].hexEditBuffer.size(),
                ImGuiInputTextFlags_CharsHexadecimal);

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                context.moveEntries[j].ApplyHexEdit();
            }

            // Column 2: ID
            ImGui::TableSetColumnIndex(1);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputScalar("##ID",
                ImGuiDataType_U16,
                &context.moveEntries[j].id,
                NULL,
                NULL,
                "%04X");

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                context.moveEntries[j].SetId(context.moveEntries[j].id);
            }

            // Column 3: Type
            ImGui::TableSetColumnIndex(2);
            ImGui::SetNextItemWidth(-FLT_MIN);
            int typeValue = context.moveEntries[j].type;

            if (ImGui::Combo("##Type",
                &typeValue,
                kTypeLabels,
                IM_ARRAYSIZE(kTypeLabels)))
            {
                context.moveEntries[j].type = static_cast<uint8_t>(typeValue);
                context.moveEntries[j].SetType(context.moveEntries[j].type);
            }

            // Column 4: Category
            ImGui::TableSetColumnIndex(3);
            ImGui::SetNextItemWidth(-FLT_MIN);
            const char* preview = CategoryLabel(context.moveEntries[j].category);

            if (ImGui::BeginCombo("##Category", preview))
            {
                for (const auto& option : kCategoryOptions)
                {
                    bool selected = (context.moveEntries[j].category == option.value);

                    if (ImGui::Selectable(option.label, selected))
                    {
                        context.moveEntries[j].category = option.value;
                        context.moveEntries[j].SetCategory(context.moveEntries[j].category);
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
            auto it = waza.moveNames.find(context.moveEntries[j].id);

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
                &context.moveEntries[j].impact,
                NULL,
                NULL,
                "%02X");

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                context.moveEntries[j].SetImpact(context.moveEntries[j].impact);
            }

            // Column 7: Head
            ImGui::TableSetColumnIndex(6);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputScalar("##Head",
                ImGuiDataType_U8,
                &context.moveEntries[j].head,
                NULL,
                NULL,
                "%02X");

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                context.moveEntries[j].SetHead(context.moveEntries[j].head);
            }

            // Column 8: Torso
            ImGui::TableSetColumnIndex(7);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputScalar("##Torso",
                ImGuiDataType_U8,
                &context.moveEntries[j].torso,
                NULL,
                NULL,
                "%02X");

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                context.moveEntries[j].SetTorso(context.moveEntries[j].torso);
            }

            // Column 9: Arms
            ImGui::TableSetColumnIndex(8);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputScalar("##Arms",
                ImGuiDataType_U8,
                &context.moveEntries[j].arms,
                NULL,
                NULL,
                "%02X");

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                context.moveEntries[j].SetArms(context.moveEntries[j].arms);
            }

            // Column 10: Legs
            ImGui::TableSetColumnIndex(9);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputScalar("##Legs",
                ImGuiDataType_U8,
                &context.moveEntries[j].legs,
                NULL,
                NULL,
                "%02X");

            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                context.moveEntries[j].SetLegs(context.moveEntries[j].legs);
            }

            // Column 11: Total
            ImGui::TableSetColumnIndex(10);
            ImGui::Text("%02X", context.moveEntries[j].total);

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
                context.moveEntries.insert(context.moveEntries.begin() + j + 1, NewEntry);
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
                context.moveEntries.erase(context.moveEntries.begin() + j);
                --j;
                --context.moveCount;
            };

            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}