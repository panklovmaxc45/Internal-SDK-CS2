#define IMGUI_DEFINE_MATH_OPERATORS
#define _USE_MATH_DEFINES
#define IMGUI_DEFINE_PLACEMENT_NEW
#undef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS

#include "custom_widgets.hpp"
#include <vector>

using namespace ImGui;


namespace custom {

   
    struct checkbox_state
    {
        ImVec4 text, filled, shadow_opacity;
    };

    bool Checkbox(const char* label, bool* v)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;

        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);

        const float w = GetWindowWidth();
        const ImVec2 pos = window->DC.CursorPos;

        const ImRect rect(pos - ImVec2(5, 0), pos + ImVec2(8, 12));
        const ImRect total_bb(pos, pos + ImVec2(w, label_size.y));

        ItemSize(ImRect(total_bb.Min, total_bb.Max - ImVec2(0, 13)));
        if (!ItemAdd(total_bb, id))
        {
            IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
            return false;
        }

        bool hovered, held;
        bool pressed = ButtonBehavior(rect, id, &hovered, &held);
        if (pressed)
        {
            *v = !(*v);
            MarkItemEdited(id);
        }

        static std::map<ImGuiID, checkbox_state> anim;
        auto it_anim = anim.find(id);

        if (it_anim == anim.end())
        {
            anim.insert({ id, checkbox_state() });
            it_anim = anim.find(id);
        }

        it_anim->second.filled = ImLerp(it_anim->second.filled, *v ? colors::accent_color : hovered ? colors::checkbox::checkbox_bg_inactive : colors::checkbox::checkbox_bg_inactive, g.IO.DeltaTime * 6.f);
        it_anim->second.shadow_opacity = ImLerp(it_anim->second.shadow_opacity, *v ? colors::accent_color : hovered ? colors::checkbox::shadow_inactive : colors::checkbox::shadow_inactive, g.IO.DeltaTime * 6.f);

        window->DrawList->AddRectFilled(rect.Min, rect.Max, GetColorU32(it_anim->second.filled));
        window->DrawList->AddRect(rect.Min, rect.Max, GetColorU32(colors::checkbox::rect));
        window->DrawList->AddShadowRect(rect.Min, rect.Max, GetColorU32(it_anim->second.shadow_opacity), 8.f, ImVec2(0, 0));
        window->DrawList->AddText(fonts::sans_font, 16.f, rect.Min + ImVec2(26, -3), ImGui::GetColorU32(colors::checkbox::text_active), label);

        return pressed;
    }
}