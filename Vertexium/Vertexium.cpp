#include "Vertexium.hpp"

void MESH::translate(float x, float y, float z)
{
	return;
}
void MESH::rotate(float x, float y, float z)
{
	return;
}

void D3D::CreateBuffers(const VERTEX* myVer, int numVerx)
{

	D3D11_BUFFER_DESC bufferDesc;
	RtlZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(VERTEX) * numVerx;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	device->CreateBuffer(&bufferDesc, NULL, &p_VertexBuffer);

	D3D11_MAPPED_SUBRESOURCE mappedSR;
	RtlZeroMemory(&mappedSR, sizeof(D3D11_MAPPED_SUBRESOURCE));
	context->Map(p_VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSR);
	memcpy_s(mappedSR.pData, sizeof(VERTEX) * numVerx, myVer, sizeof(VERTEX) * numVerx);
	context->Unmap(p_VertexBuffer, NULL);
}
void D3D::CompileShaders(void)
{
	HRESULT hrVertexShader = D3DCompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, &vertexShader, 0);
	HRESULT hrPixelShader = D3DCompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, &pixelShader, 0);

	device->CreateVertexShader(vertexShader->GetBufferPointer(), vertexShader->GetBufferSize(), NULL, &p_VertexShader);
	device->CreatePixelShader(pixelShader->GetBufferPointer(), pixelShader->GetBufferSize(), NULL, &p_PixelShader);

	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	device->CreateInputLayout(inputElementDesc, 2, vertexShader->GetBufferPointer(), vertexShader->GetBufferSize(), &layout);
	context->IASetInputLayout(layout);
	
}
void D3D::InitD3D(HWND hWnd)
{

	RtlZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	RtlZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FrontCounterClockwise = FALSE;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.ScissorEnable = FALSE;
	rasterizerDesc.MultisampleEnable = FALSE;
	rasterizerDesc.AntialiasedLineEnable = FALSE;

	swapChainDesc.BufferCount = 1;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 4;
	swapChainDesc.BufferDesc.Width = 800;
	swapChainDesc.BufferDesc.Height = 800;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D11CreateDeviceAndSwapChain
	(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&device,
		NULL,
		&context
	);

	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&p_BackBuffer);
	device->CreateRenderTargetView(p_BackBuffer, NULL, &backBuffer);
	p_BackBuffer->Release();
	context->OMSetRenderTargets(1, &backBuffer, NULL);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 800;
	context->RSSetViewports(1, &viewport);
}
void D3D::ReleaseD3D(IDXGISwapChain* sc, ID3D11Device* dev, ID3D11DeviceContext* con, ID3D11Texture2D* bb, ID3D11VertexShader* vs, ID3D11PixelShader* ps)
{
	void* toRelease[] = { sc, dev, con, bb, vs, ps };

	//iterates each struct and releases if <> nullptr
	//if client terminates the program, the CPU/GPU mem allocations may be prematurely released before safely released by the program 
	for (void* aPointer : toRelease) { if (aPointer) { reinterpret_cast<IUnknown*>(aPointer)->Release(); } }

}
void D3D::RenderFrame(void)
{

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;

	context->ClearRenderTargetView(backBuffer, viewport_background);
	
	context->IASetVertexBuffers(0, 1, &p_VertexBuffer, &stride, &offset);
	context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->VSSetShader(p_VertexShader, nullptr, 0);
	context->PSSetShader(p_PixelShader, nullptr, 0);

	context->IASetInputLayout(layout);

	context->Draw(300,0);
	swapChain->Present(0, 0);
}
void D3D::DebugMemoryAddressesAndCompilation(void)
{
	std::ofstream outputFile("output.txt");
	outputFile << "Vertex Shader Blob: " << vertexShader << std::endl;
	outputFile << "Compiled Vertex Shader: " << p_VertexShader << std::endl;
	outputFile << "Pixel Shader Blob: " << pixelShader << std::endl;
	outputFile << "Compiled Pixel Shader: " << p_PixelShader << std::endl;
	outputFile << "Vertex Buffer: " << p_VertexBuffer << std::endl;
	outputFile << "\n BREAK \n BREAK \n BREAK" << std::endl;
	outputFile.close();
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}	break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
