#include "Graphics.hpp"
#include "GraphicAdapter.hpp"

Graphics::GraphicsHrException::GraphicsHrException(int line, const char* file, HRESULT hr) noexcept : HrException(line, file, hr) {}

const wchar_t* Graphics::GraphicsHrException::GetType() const noexcept
{
	return L"GraphicsHrException";
}

Graphics::InfoGraphicsHrException::InfoGraphicsHrException(int line, const char* file, HRESULT hr, std::wstring info) noexcept : GraphicsHrException(line, file, hr), info(info) {}

Graphics::InfoGraphicsHrException::InfoGraphicsHrException(int line, const char* file, HRESULT hr, std::vector<std::wstring> info) noexcept : GraphicsHrException(line, file, hr)
{
	std::wostringstream oss;
	for (auto&& str : info)
		oss << str;
	this->info = oss.str();
}

const wchar_t* Graphics::InfoGraphicsHrException::GetType() const noexcept
{
	return L"InfoGraphicsHrException";
}

const wchar_t* Graphics::InfoGraphicsHrException::what() const noexcept
{
	std::wostringstream oss;
	oss << GetType() << std::endl
		<< L"Info: " << info << std::endl
		<< HrErrorString()
		<< GetErrorLocation();
	buffer = oss.str();
	return buffer.c_str();
}

Graphics::InfoGraphicsException::InfoGraphicsException(int line, const char* file, std::wstring info) noexcept : EngineException(line, file), info(info) {}

Graphics::InfoGraphicsException::InfoGraphicsException(int line, const char* file, std::vector<std::wstring> info) noexcept : EngineException(line, file)
{
	std::wostringstream oss;
	for (auto&& str : info)
		oss << str;
	this->info = oss.str();
}

const wchar_t* Graphics::InfoGraphicsException::GetType() const noexcept
{
	return L"InfoGraphicsException";
}

const wchar_t* Graphics::InfoGraphicsException::what() const noexcept
{
	std::wostringstream oss;
	oss << GetType() << std::endl
		<< L"Info: " << info << std::endl
		<< GetErrorLocation();
	buffer = oss.str();
	return buffer.c_str();
}

Graphics::Graphics(HWND hWnd, int width, int height) : windowWidth(width), windowHeight(height)
{
	InitializeDirectX(hWnd);
	Initialize();
}

void Graphics::RenderFrame()
{
	PreProcessing();
	Processing();
	PostProcessing();
}
void Graphics::PreProcessing()
{
	float bgcolor[] = { 0.92f, 0.24f, 0.24f, 1.0f };
	deviceContext->ClearRenderTargetView(renderTargetView.Get(), bgcolor);
	deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	deviceContext->OMSetDepthStencilState(depthStencilState.Get(), 0);
	deviceContext->RSSetState(rasterizerState.Get());
	deviceContext->PSSetSamplers(0, 1, samplerState.GetAddressOf());




	deviceContext->IASetInputLayout(vertexShader.GatInputLoyout());
	deviceContext->VSSetShader(vertexShader.GetShader(), NULL, 0);
	deviceContext->PSSetShader(pixelShader.GetShader(), NULL, 0);

}

void Graphics::Processing()
{

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	deviceContext->PSSetShaderResources(0, 1, texture.GetAddressOf());
	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offset);
	deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	deviceContext->DrawIndexed(indexBuffer.BufferSize(), 0, 0);
}

void Graphics::PostProcessing()
{
	swapchain->Present(1, NULL);
}

/*
1  Input Assembler		(IA) Stage
2  Vertex Shader		(VS) Stage
3  Hull Shader			(HS) Stage
4  Tessellator Shader	(TS) Stage
5  Domain Shader		(DS) Stage
6  Geometry Shader		(GS) Stage
7  Stream Output		(SO) Stage
8  Rasterizer			(RS) Stage
9  Pixel Shader			(PS) Stage
10 Output Merger		(OM) Stage
*/
void Graphics::InitializeDirectX(HWND hWnd)
{
	std::vector<GraphicAdapter> adapters = GraphicAdapter::GetGraphicAdapters();
	if (adapters.size() < 1)
		throw GFX_INFO_EXCEPTION(L"No found DXGI Adapters.");

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferDesc.Width = windowWidth;
	scd.BufferDesc.Height = windowHeight;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hWnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr = 0;

	hr = D3D11CreateDeviceAndSwapChain(
		adapters[0].pAdapter,			// Adapter
		D3D_DRIVER_TYPE_UNKNOWN,		// DriverType
		NULL,							// Software
		NULL,							// Flags
		NULL,							// FeatureLevels
		0,								// FeatureLevels
		D3D11_SDK_VERSION,				// SDKVersion
		&scd,							// SwapChainDesc
		swapchain.GetAddressOf(),		// SwapChain
		device.GetAddressOf(),			// Device
		NULL,							// FeatureLevel
		deviceContext.GetAddressOf()	// ImmediateContext
	);
	GFX_ERROR_IF(hr, L"Failed to create device and swapchain.");

	com_ptr<ID3D11Texture2D> backBuffer;
	hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	GFX_ERROR_IF(hr, L"Failed to create backBuffer.");



	// Render Target
	hr = device->CreateRenderTargetView(backBuffer.Get(), NULL, renderTargetView.GetAddressOf());
	GFX_ERROR_IF(hr, L"Failed to create RenderTargetView.");

	// Depth
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = windowWidth;
	depthStencilDesc.Height = windowHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hr = device->CreateTexture2D(&depthStencilDesc, NULL, depthStencilBuffer.GetAddressOf());
	GFX_ERROR_IF(hr, L"Failed to create depth stencil buffer.");

	hr = device->CreateDepthStencilView(depthStencilBuffer.Get(), NULL, depthStencilView.GetAddressOf());
	GFX_ERROR_IF(hr, L"Failed to create depth stencil view.");

	this->deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());



	// Depth Stencil State
	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
	ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthStencilStateDesc.DepthEnable = true;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
	hr = device->CreateDepthStencilState(&depthStencilStateDesc, depthStencilState.GetAddressOf());
	GFX_ERROR_IF(hr, L"Failed to create depth stencil state.");



	// Rasterizer state
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID; // Fill the triangles formed by the vertices. Adjacent vertices are not drawn.
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;	 // Do not draw triangles that are back-facing.
	hr = device->CreateRasterizerState(&rasterizerDesc, rasterizerState.GetAddressOf());
	GFX_ERROR_IF(hr, L"Failed to create rasterizer state.");



	// Sampler state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = device->CreateSamplerState(&sampDesc, samplerState.GetAddressOf());
	GFX_ERROR_IF(hr, L"Failed to create sampler state.");




	// viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<FLOAT>(windowWidth);
	viewport.Height = static_cast<FLOAT>(windowHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	deviceContext->RSSetViewports(1, &viewport);

}

void Graphics::Initialize()
{
	// Shaders
	D3D11_INPUT_ELEMENT_DESC loyout[]
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{"NORMAL", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(loyout);
	vertexShader.Initalize(device, Paths::ShaderFolder + L"VertexShader.cso", loyout, numElements);
	pixelShader.Initalize(device, Paths::ShaderFolder + L"PixelShader.cso");



	// Scene
	Vertex v[]
	{
		{-0.5f, -0.5f, 1.0f, 0.0f, 1.0f},
		{-0.5f,  0.5f, 1.0f, 0.0f, 0.0f},
		{ 0.5f,  0.5f, 1.0f, 1.0f, 0.0f},
		{ 0.5f, -0.5f, 1.0f, 1.0f, 1.0f},
	};
	HRESULT hr = vertexBuffer.Initialize(device.Get(), v, ARRAYSIZE(v));
	GFX_ERROR_IF(hr, L"Failed to create vertex buffer.");

	DWORD indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};
	hr = indexBuffer.Initialize(device.Get(), indices, ARRAYSIZE(indices));
	GFX_ERROR_IF(hr, L"Failed to create index buffer.");




	hr = DirectX::CreateWICTextureFromFile(device.Get(), L"Data\\Textures\\cat.jpg", nullptr, texture.GetAddressOf());
	GFX_ERROR_IF(hr, L"Failed to load texture from file.");

}