#include "Menu.h"
#include "Config.h"
#include <imgui/custom_widgets.hpp>

void Style()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0f;
    style.DisabledAlpha = 1.0f;
    style.WindowPadding = ImVec2(12.0f, 12.0f);
    style.WindowRounding = 3.0f;
    style.WindowBorderSize = 0.0f;
    style.WindowMinSize = ImVec2(20.0f, 20.0f);
    style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Right;
    style.ChildRounding = 6.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 6.0f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(20.0f, 8.0f);
    style.FrameRounding = 6.0f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(7.900000095367432f, 6.0f);
    style.ItemInnerSpacing = ImVec2(6.0f, 3.0f);
    style.CellPadding = ImVec2(12.0f, 6.0f);
    style.IndentSpacing = 20.0f;
    style.ColumnsMinSpacing = 20.0f;
    style.ScrollbarSize = 15.89999961853027f;
    style.ScrollbarRounding = 20.0f;
    style.GrabMinSize = 10.0f;
    style.GrabRounding = 20.0f;
    style.TabRounding = 6.0f;
    style.TabBorderSize = 1.0f;
    style.TabMinWidthForCloseButton = 10.0f;
    style.ColorButtonPosition = ImGuiDir_Left;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    style.Colors[ImGuiCol_WindowBg] = ImColor(23, 23, 23, 255);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1276470592617989f, 0.1433333402872086f, 0.1590196138620377f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1376470592617989f, 0.1533333402872086f, 0.1690196138620377f, 1.0f);
}

void Gui::Render()
{
    Style();
    ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    ImGui::Begin("ImGui Window", nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    {
         ImGui::SetCursorPos(ImVec2(15, 10));
         custom::Checkbox("Esp Enable", &VisualsConfig.ENABLE);
         if (VisualsConfig.ENABLE)
         {
             ImGui::SetCursorPos(ImVec2(15, 30));
             custom::Checkbox("Bounding Box", &VisualsConfig.BOUNDING_BOX);
         
             ImGui::SetCursorPos(ImVec2(15, 50));
             custom::Checkbox("Health Bar", &VisualsConfig.HEALTH_BAR);
         }
    }
    ImGui::End();
}