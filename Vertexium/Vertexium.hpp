#pragma once

#include <Windows.h>
#include <Windowsx.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <tuple>
#include <vector>
#include <iostream>
#include <fstream>

#pragma once
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#pragma warning(disable : 28251)
#pragma warning(disable : 6387)
#pragma warning(disable : 26495)

typedef float RGBA[4];
struct VERTEX
{
	float x, y, z;
	RGBA color;
};

typedef std::vector<VERTEX> MESHVEC;
class MESH
{
	private:
		MESHVEC m_vecs;
	public:
		void translate(float x, float y, float z);
		void rotate(float x, float y, float z);
};

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class D3D
{
	public:

		float viewport_width = 800.0f;
		float viewport_height = 800.0f;
		float viewport_background[4] = { 0.0f,0.0f,0.0f,1.0f };

		IDXGISwapChain* swapChain;
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ID3D11Device* device;
		ID3D11DeviceContext* context;
		D3D11_RASTERIZER_DESC* rasterizerDesc;
		ID3D11RenderTargetView* backBuffer;
		ID3D11Texture2D* pBackBuffer;
		D3D11_VIEWPORT  viewport;
		ID3D10Blob* pixelShader;
		ID3D10Blob* vertexShader;
		ID3D11InputLayout* layout;
		D3D11_MAPPED_SUBRESOURCE* mappedSR;
		ID3D11VertexShader* p_VertexShader = nullptr;
		ID3D11PixelShader* p_PixelShader = nullptr;
		ID3D11Buffer* p_VertexBuffer = nullptr;

		friend VERTEX;

		void InitD3D(HWND hWnd);
		void CompileShaders(void);
		void CreateBuffers(const VERTEX* myVer);
		void ReleaseD3D(IDXGISwapChain* sc, ID3D11Device* dev, ID3D11DeviceContext* con, ID3D11Texture2D* bb, ID3D11VertexShader* vs, ID3D11PixelShader* ps);
		void RenderFrame(void);
};
