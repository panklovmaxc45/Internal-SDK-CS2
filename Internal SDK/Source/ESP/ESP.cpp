#include "ESP.h"

void DrawEntity(const Entities::Entity& Entity, ImDrawList* DrawList) 
{
    const auto ViewMatrix = reinterpret_cast<float(*)[4][4]>(Entities::Client + Offsets::ViewMatrix);
    const auto LocalPawn = *reinterpret_cast<uintptr_t*>(Entities::Client + Offsets::LocalPlayer);
    const auto LocalPosition = *reinterpret_cast<Vector3*>(LocalPawn + Offsets::OldOrigin);

    Vector2 Feet, Head;
    if (Entity.FeetPos.WTS(Feet, ViewMatrix, SCREEN_WIDTH, SCREEN_HEIGHT) && Entity.HeadPos.WTS(Head, ViewMatrix, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        float Height = Feet.Y - Head.Y;
        float Width = Height * 0.5f;

        ImVec2 BoxMin = { Feet.X - Width / 2, Head.Y };
        ImVec2 BoxMax = { Feet.X + Width / 2, Head.Y + Height };

        ImColor OutlineColor = ImColor(0, 0, 0);

        if (VisualsConfig.BOUNDING_BOX)
        {
            DrawList->AddRect(BoxMin - ImVec2(1.0f, 1.0f), BoxMax + ImVec2(1.0f, 1.0f), OutlineColor, 0.0f, 0, 1.0f);
            DrawList->AddRect(BoxMin + ImVec2(1.0f, 1.0f), BoxMax - ImVec2(1.0f, 1.0f), OutlineColor, 0.0f, 0, 1.0f);
            DrawList->AddRect(BoxMin, BoxMax, ImColor(VisualsConfig.BOUNDING_BOX_COLOR), 0.0f, 0, 1.0f);
        }

        if (VisualsConfig.HEALTH_BAR)
        {
            constexpr float BAR_WIDTH = 1.0f;       
            constexpr float OFFSET = 3.0f;          

            const float BarLeft = Feet.X - Width / 2 - OFFSET - BAR_WIDTH;
            const float BarTop = Head.Y;
            const float BarBottom = BarTop + Height;
            const float BarHeight = Height * (Entity.Health / 100.0f);

            DrawList->AddRect(ImVec2(BarLeft - 0.5f, BarTop - 0.5f), ImVec2(BarLeft + BAR_WIDTH + 0.5f, BarBottom + 0.5f), IM_COL32(0, 0, 0, 255), 0.0f, 0, 1.0f);
            DrawList->AddRectFilled(ImVec2(BarLeft, BarBottom - BarHeight), ImVec2(BarLeft + BAR_WIDTH, BarBottom), ImColor(VisualsConfig.HEALTH_BAR_COLOR));
        }
    }
}

void Render::Players() {
    CEntities->UpdateEntity();

    ImDrawList* DrawList = ImGui::GetBackgroundDrawList();

    for (const auto& Entity : CEntities->GetEntities())
        DrawEntity(Entity, DrawList);
}
