#include "Vertexium.hpp"

const VERTEX VERTICES[3] =
{
    { 0.0f,  0.5f, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f }},   
    {-0.5f, -0.5f, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f }},   
    { 0.5f, -0.5f, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f }},

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
    myD3D->InitD3D(hWnd);
    myD3D->CompileShaders();
    myD3D->CreateBuffers(VERTICES);

                                                                //Mem address to .txt in order of instantiation
                                            std::ofstream outputFile("output.txt");
                                            outputFile << "Vertex Shader Blob: " << myD3D->vertexShader << std::endl;
                                            outputFile << "Compiled Vertex Shader: " << myD3D->p_VertexShader << std::endl;
                                            outputFile << "Pixel Shader Blob: " << myD3D->pixelShader << std::endl;
                                            outputFile << "Compiled Pixel Shader: " << myD3D->p_PixelShader << std::endl;
                                            outputFile << "Vertex Buffer: " << myD3D->p_VertexBuffer << std::endl;
                                            outputFile << "\n BREAK \n BREAK \n BREAK" << std::endl;
                                            outputFile.close();


    MSG message;
    std::ofstream coordFile("coord_test.txt", std::ios::app);
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
            std::ofstream coordFile("coord_test.txt");
            coordFile << "Viewport Width: " << myD3D->viewport.Width << ", Height: " << myD3D->viewport.Height << std::endl;
            for (int i = 0; i < 3; ++i)
            {
                coordFile << "Vertex " << i << " - X: " << VERTICES[i].x << ", Y: " << VERTICES[i].y << std::endl;
            }

        }
    }

    myD3D->ReleaseD3D(myD3D->swapChain, myD3D->device, myD3D->context, myD3D->pBackBuffer, myD3D->p_VertexShader, myD3D->p_PixelShader);
    return message.wParam;
}