#pragma once
#include <imgui/imgui.h>
#include <Entity/Entity.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <libloaderapi.h>

struct VisualConfig {
	inline static bool ENABLE;
	inline static bool BOUNDING_BOX;
	inline static bool HEALTH_BAR;
	inline static bool ESP_OUT_OF_VIEW;

	inline static ImVec4 BOUNDING_BOX_COLOR = ImColor(255, 255, 255);
	inline static ImVec4 HEALTH_BAR_COLOR = ImColor(255, 255, 255);
};
inline VisualConfig VisualsConfig;
