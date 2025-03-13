#pragma once
#include <cstdint>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <string>
#include <ImGui/imgui.h>
#include "Misc/Config.h"

static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

namespace Render {
	void Players();
}