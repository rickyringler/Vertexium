#pragma once

#include "PCHs.hpp"

class WindowBase
{
    public:

    protected:

    private:

};

class VWindow final : WindowBase
{
    public:
        VWindow(LPCWSTR class_name, HINSTANCE hInstance);
        ~VWindow();

        static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        void ConstructWindow(int x, int y, int height, int width, const wchar_t* title, HINSTANCE hInstance, HWND& hWnd);
        void DisplayWindow(HWND hWnd, int nCmdShow);

    private:
        int x = 0, y = 0, height = 0, width = 0;
        const wchar_t* title=L"DEFAULT";
        LPCWSTR class_name;
        HINSTANCE hInstance;

        int HandleWinMessage(MSG& message);
};
