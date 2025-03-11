#pragma once

#include "imgui.h"

namespace colors {

    inline ImVec4 accent_color = ImColor(255, 255, 255);

    inline ImVec4 text = ImColor(255, 255, 255);

    namespace checkbox {

        inline ImVec4 text_active = ImColor(255, 255, 255);
        inline ImVec4 text_hovered = ImColor(150, 150, 150);
        inline ImVec4 text_inactive = ImColor(76, 76, 77);
        inline ImVec4 shadow_inactive = ImColor(0, 0, 0, 0);
        inline ImVec4 checkbox_bg_inactive = ImColor(36, 37, 39);
        inline ImVec4 rect = ImColor(5, 5, 5);

    }
}

namespace settings {
    inline float checkbox_rounding = 100.f;
}

