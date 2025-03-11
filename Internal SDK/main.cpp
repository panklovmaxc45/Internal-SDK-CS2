#define _CRT_SECURE_NO_WARNINGS
#include "includes.h"
#include <iostream>
#include <ESP/ESP.h>

const int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int SCREEN_HEIGHT = GetSystemMetrics(SM_CXSCREEN);

bool IS_MENU_VISIBLE = true;
bool init = false;
bool IsEsp = false;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;

    fonts::sans_font = io.Fonts->AddFontFromMemoryTTF(&sans, sizeof sans, 18, NULL, io.Fonts->GetGlyphRangesCyrillic());

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (IS_MENU_VISIBLE) {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
            return TRUE; 
        }
        switch (uMsg) {
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_MOUSEWHEEL:
        case WM_MOUSEHWHEEL:
            if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) || !ImGui::GetIO().WantCaptureMouse) {
                return TRUE; 
            }
            break;
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_CHAR:
            if (!ImGui::GetIO().WantCaptureKeyboard) {
                return TRUE; 
            }
            break;
        default:
            break;
        }
    }
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            pBackBuffer->Release();
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
            InitImGui();
            init = true;
            std::cout << "Cheat Success Hooked!" << std::endl;
        }
        else
            return oPresent(pSwapChain, SyncInterval, Flags);
    }

    static bool lastInsertState = false;
    bool currentInsertState = GetAsyncKeyState(VK_INSERT) & 0x8000;
    if (currentInsertState && !lastInsertState) {
        IS_MENU_VISIBLE = !IS_MENU_VISIBLE;
        if (IS_MENU_VISIBLE) {
            ImGui::GetIO().MouseDrawCursor = true;
            ImGui::GetIO().WantCaptureMouse = true;
            ImGui::GetIO().WantCaptureKeyboard = true;
            ImGui::GetIO().WantTextInput = true;
        }
        else {
            ImGui::GetIO().MouseDrawCursor = false;
            ImGui::GetIO().WantCaptureMouse = false;
            ImGui::GetIO().WantCaptureKeyboard = false;
            ImGui::GetIO().WantTextInput = false;
        }
    }
    lastInsertState = currentInsertState;

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (IsEsp)
    {
        Render::Players();
    }

    if (IS_MENU_VISIBLE) {
        ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
        ImGui::Begin("ImGui Window", &IS_MENU_VISIBLE, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        {
            ImGui::SetCursorPos(ImVec2(15, 10));
            custom::Checkbox("Esp Enabled", &IsEsp);
        }
        ImGui::End();

        ImGui::GetIO().WantCaptureMouse = true;
        ImGui::GetIO().WantCaptureKeyboard = true;
        ImGui::GetIO().WantTextInput = true;
    }
    else {
        ImGui::GetIO().WantCaptureMouse = false;
        ImGui::GetIO().WantCaptureKeyboard = false;
        ImGui::GetIO().WantTextInput = false;
        ImGui::GetIO().MouseDrawCursor = false;
    }

    ImGui::Render();

    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    bool init_hook = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&oPresent, hkPresent);
            init_hook = true;
        }
    } while (!init_hook);
    return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod);
        CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        kiero::shutdown();
        break;
    }
    return TRUE;
}