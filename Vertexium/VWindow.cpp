#include "VWindow.hpp"

LRESULT CALLBACK VWindow::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

void VWindow::ConstructWindow(int x, int y, int height, int width, const wchar_t* title, HINSTANCE hInstance, HWND& hWnd)
{
    this->x = x;
    this->y = y;
    this->height = height;
    this->width = width;
    this->title = title;

    hWnd = CreateWindowEx
    (
        0,
        class_name,
        title,
        WS_OVERLAPPEDWINDOW,

        x, y, width, height,

        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hWnd == NULL){}
}

int VWindow::HandleWinMessage(MSG& message)
{
    if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
        if (message.message == WM_QUIT)
        {
            return 0;
        }
    }
    return 1;
}

void VWindow::DisplayWindow(HWND hWnd, int nCmdShow)
{
    ShowWindow(hWnd, nCmdShow);
    MSG message;
    while (HandleWinMessage(message));
}

VWindow::VWindow(LPCWSTR class_name, HINSTANCE hInstance)
    : class_name(class_name), hInstance(hInstance)
{
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WinProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(0, IDI_APPLICATION);
    wc.lpszClassName = class_name;

    RegisterClassEx(&wc);
}

VWindow::~VWindow()
{
}
