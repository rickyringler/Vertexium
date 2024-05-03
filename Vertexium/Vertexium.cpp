/*

Here is a little tutorial on how graphics rendering works within the context of DX.
There are notes near most lines of code to explain, but it makes sense to read this first section beforehand.

C++ calls the DirectX API.
The DirectX API calls the device driver.
The device driver translates high-level code into machine code for the GPU.
The GPU digests and performs a function.

DirectX: Cohort of Microsoft APIs. Sends requests to device drivers.
    Direct3D - three dimension rendering
    DirectDraw - two dimension rendering
    DirectSound - audio streams, buffers, and manipulation
    DirectInput - device input (keyboards, mouse, controllers)
    DirectPlay - networking
    DirectWrite - modern text renderer
    DirectMedia - playback for video and audio

Device driver: Hardware abstraction, processing.
    NVIDIA
    AMD Radeon
    Intel

D3DLL : DirectX library for creating device, context, and swap chain.

D3DCompiler : Component of D3D used in high-quality graphics rendering functions.

Render target: Where rendering will be directed to (data goes here to be used by the Viewport)
    Ex: An object in a scene. Technically, the scene itself too.

Viewport: Where the rendered images will appear. The magical space where the scene is allowed to exist.

*/





#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>
#include "Vertex.hpp"

#pragma comment(lib, "d3d11.lib") //Create DX device, swap chain, target view, and context
#pragma comment(lib, "d3dcompiler.lib") //D3DCompile - compile HLSL into bytecode

int win_width = 500;
int win_height = 600;
int dx_buffer = 1;

struct WinDXParameters
{
    int win_width = 500;
    int win_height = 600;
    int dx_buffer = 1;
    int dx_back_buffer = 1;
};

WinDXParameters* parameters = new WinDXParameters;

//How to handle Windows messages
//LRESULT is used by the Windows API to store Windows messages
//CALLBACK is used to define a function intended to communicate with the Windows API
//WindowProc processes messages to a Window
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
};

//Creates Windows instance
int WINAPI main(HINSTANCE h_instance, HINSTANCE h_instance_previous, LPSTR lp_cmd_line, int cmd_show)
{
    //Define type of Window
    WNDCLASS window_class = {};
    window_class.lpfnWndProc = WindowProc;
    window_class.hInstance = h_instance;
    const wchar_t class_name[] = L"DXWindow";
    window_class.lpszClassName = class_name;

    //Registers the Window
    RegisterClass(&window_class);

    //Handle for Window
    HWND hwnd = CreateWindowEx(0,
        class_name,
        L"DirectX Triangle",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        parameters->win_width,
        parameters->win_height,
        NULL,
        NULL,
        h_instance,
        NULL);

    DXGI_SWAP_CHAIN_DESC dx_sc = { 0 }; //Intialize all buffer values to 0
    dx_sc.BufferCount = parameters->dx_buffer; // 1
    dx_sc.BufferDesc.Width = parameters->win_width; //Width of buffer
    dx_sc.BufferDesc.Height = parameters->win_height; //Height of buffer
    dx_sc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; //32 bit pixels with 8 for BGRA (8*4)
    dx_sc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    dx_sc.OutputWindow = hwnd; //Handle for Window
    dx_sc.SampleDesc.Count = 1;
    dx_sc.Windowed = TRUE; //Windowed instead of entire screen (application)

    D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0 }; //Specifies hardware requirements
    ID3D11Device* device = nullptr; //Create device
    ID3D11DeviceContext* context = nullptr; //Create context
    IDXGISwapChain* swap_chain = nullptr; //Create swap chain
    
    //Defines DX device and swap chain
    D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, feature_levels, 1, D3D11_SDK_VERSION, &dx_sc, &swap_chain, &device, NULL, &context);


    //Defines RTV from DX
    ID3D11RenderTargetView* render_target_view = nullptr;
    ID3D11Texture2D* back_buffer = nullptr;
    swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&back_buffer));
    device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
    back_buffer->Release();

    context->OMSetRenderTargets(1, &render_target_view, nullptr);

    //Defines Viewport from DX
    D3D11_VIEWPORT viewport = {};
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = static_cast<float>(win_width);
    viewport.Height = static_cast<float>(win_height);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    context->RSSetViewports(1, &viewport);

    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
        }
    }

    return 0;
}
