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
	
}

void Graphics::Processing()
{
}

void Graphics::PostProcessing()
{

	swapchain->Present(1, NULL);
}

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
	GFX_ERROR_IF(hr, L"GetBuffer Failed.");

	hr = device->CreateRenderTargetView(backBuffer.Get(), NULL, renderTargetView.GetAddressOf());
	GFX_ERROR_IF(hr, L"Failed to create RenderTargetView.");

	this->deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), NULL);
}