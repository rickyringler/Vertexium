#include "Vertexium.hpp"

const VERTEX VERTICES[6] =
{
    { 0.0f,  0.5f, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f }},
    {-0.5f, -0.5f, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f }},
    { 0.5f, -0.5f, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f }},

    { 0.5f,  0.5f, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f }},
    { 1.0f, -0.5f, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f }},
    { 0.0f, -0.5f, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f }},
};

                                                           //forward decs
                                            HWND hWnd; WNDCLASSEX wc; class D3D;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{


    ZeroMemory(&wc, sizeof(WNDCLASSEX));

                                            wc.cbSize = sizeof(WNDCLASSEX);
                                            wc.style = CS_HREDRAW | CS_VREDRAW;
                                            wc.lpfnWndProc = WinProc;
                                            wc.hInstance = hInstance;
                                            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
                                            wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
                                            wc.hIcon = LoadIcon(0, IDI_APPLICATION);
                                            wc.hIconSm = LoadIcon(0, IDI_APPLICATION);
                                            wc.lpszClassName = L"WindowClass";

    RegisterClassEx(&wc);

    RECT wr = { 0, 0, 800, 600 };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    hWnd = CreateWindowEx
    (
                                            NULL,
                                            L"WindowClass",
                                            L"I Love Vertices <3",
                                            WS_OVERLAPPEDWINDOW,
                                            300,
                                            300,
                                            800,
                                            800,
                                            NULL,
                                            NULL,
                                            hInstance,
                                            NULL
    );

    ShowWindow(hWnd, nCmdShow);

    D3D* myD3D = new D3D;
    int myVerxToRender = 6;
    myD3D->InitD3D(hWnd);myD3D->CompileShaders();myD3D->CreateBuffers(VERTICES, myVerxToRender);myD3D->DebugMemoryAddressesAndCompilation();

    MSG message;
    while(1)
    {
        if(PeekMessage(&message, NULL,0,0,PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);

            if (message.message == WM_QUIT)
                break;

        }
        else
        {
            myD3D->RenderFrame();
        }
    }

    myD3D->ReleaseD3D(myD3D->swapChain, myD3D->device, myD3D->context, myD3D->p_BackBuffer, myD3D->p_VertexShader, myD3D->p_PixelShader);
    return message.wParam;
}