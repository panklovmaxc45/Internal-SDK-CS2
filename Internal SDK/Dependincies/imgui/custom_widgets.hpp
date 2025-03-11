#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "imgui_internal.h"
#include "widgets_colors.h"
#include <map>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <wtypes.h>
#include "imstb_textedit.h"

namespace fonts 
{
    inline ImFont* sans_font;
}

namespace custom
{
    bool Checkbox(const char* label, bool* v);
}
