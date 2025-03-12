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

        ImColor BoxColor = ImColor(255, 255, 255);
        ImColor OutlineColor = ImColor(0, 0, 0);

        DrawList->AddRect(BoxMin - ImVec2(1.0f, 1.0f), BoxMax + ImVec2(1.0f, 1.0f), OutlineColor, 0.0f, 0, 1.0f);
        DrawList->AddRect(BoxMin + ImVec2(1.0f, 1.0f), BoxMax - ImVec2(1.0f, 1.0f), OutlineColor, 0.0f, 0, 1.0f);
        DrawList->AddRect(BoxMin, BoxMax, BoxColor, 0.0f, 0, 1.0f);
    }
}

void Render::Players() {
    CEntities->UpdateEntity();

    ImDrawList* DrawList = ImGui::GetBackgroundDrawList();

    for (const auto& Entity : CEntities->GetEntities())
        DrawEntity(Entity, DrawList);
}
