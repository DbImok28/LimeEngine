#include "Graphics.hpp"
#include "GraphicAdapter.hpp"

#ifdef IMGUI
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

void Graphics::ImGuiSetup(HWND hWnd)
{
	// Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(device.Get(), deviceContext.Get());
	ImGui::StyleColorsDark();
}

void Graphics::ImGuiUpdate()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	ImGui::Begin("Test");
	ImGui::End();

	//ImGui::DragFloat3()

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
#endif // IMGUI

Graphics::Graphics(HWND hWnd, int width, int height) : windowWidth(width), windowHeight(height)
{
	InitializeDirectX(hWnd);
	Initialize();
	std::vector<Vertex> v
	{
		{-0.5f, -0.5f, -0.5f, 0.0f, 1.0f}, // front
		{-0.5f,  0.5f, -0.5f, 0.0f, 0.0f},
		{ 0.5f,  0.5f, -0.5f, 1.0f, 0.0f},
		{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f},

		{-0.5f, -0.5f, 0.5f, 0.0f, 1.0f}, // back
		{-0.5f,  0.5f, 0.5f, 0.0f, 0.0f},
		{ 0.5f,  0.5f, 0.5f, 1.0f, 0.0f},
		{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f},
	};
	std::vector<DWORD> indices =
	{
		0, 1, 2, 0, 2, 3, // front
		4, 7, 6, 4, 6, 5, // back
		3, 2, 6, 3, 6, 7, // right
		4, 5, 1, 4, 1, 0, // left
		1, 5, 6, 1, 6, 2, // top
		0, 3, 7, 0, 7, 4, // bottom
	};
	// Test
	mat.Set(deviceContext.Get(), &vertexShader, &pixelShader);
	mat.SetTextures({Texture2D(device.Get(), L"Data\\Textures\\cat.jpg", TextureType::Diffuse)});
	mesh = Mesh
	(
		device.Get(),
		deviceContext.Get(),
		{
			{-0.5f, -0.5f, -0.5f, 0.0f, 1.0f}, // front
			{-0.5f,  0.5f, -0.5f, 0.0f, 0.0f},
			{ 0.5f,  0.5f, -0.5f, 1.0f, 0.0f},
			{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f},

			{-0.5f, -0.5f, 0.5f, 0.0f, 1.0f}, // back
			{-0.5f,  0.5f, 0.5f, 0.0f, 0.0f},
			{ 0.5f,  0.5f, 0.5f, 1.0f, 0.0f},
			{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f},
		},
		{
			0, 1, 2, 0, 2, 3, // front
			4, 7, 6, 4, 6, 5, // back
			3, 2, 6, 3, 6, 7, // right
			4, 5, 1, 4, 1, 0, // left
			1, 5, 6, 1, 6, 2, // top
			0, 3, 7, 0, 7, 4, // bottom
		},
		mat,
		XMMatrixIdentity()
	);
#ifdef IMGUI
	ImGuiSetup(hWnd);
#endif // IMGUI
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


	/*deviceContext->IASetInputLayout(vertexShader.GatInputLoyout());
	deviceContext->VSSetShader(vertexShader.GetShader(), NULL, 0);
	deviceContext->PSSetShader(pixelShader.GetShader(), NULL, 0);*/
}

void Graphics::Processing()
{

	/*UINT stride = sizeof(Vertex);*/
	/*UINT offset = 0;*/

	/*deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offset);
	deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);*/

	/*constantBuffer.data.wvpMatrix = XMMatrixTranspose(camera.GetViewProjectionMatrix());
	constantBuffer.ApplyChanges();
	deviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());*/

	//deviceContext->PSSetShaderResources(0, 1, texture.GetAddressOf());
	static ConstantBuffer<CB_VS_VertexShader> constantBuffer;
	constantBuffer.Initialize(device.Get(), deviceContext.Get());
	constantBuffer.data.wvpMatrix = XMMatrixTranspose(mesh.GetTransformMatrix() * camera.GetViewProjectionMatrix());
	mat.ApplyConstantBuffer(constantBuffer);
	mesh.Draw();
	//deviceContext->DrawIndexed(indexBuffer.BufferSize(), 0, 0);
}

void Graphics::PostProcessing()
{
#ifdef IMGUI
	ImGuiUpdate();
#endif // IMGUI

	HRESULT hr;
	GFX_ERROR_INFO;
	if (FAILED(hr = swapchain->Present(1, NULL)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
			throw GFX_HR_EXCEPTION(device->GetDeviceRemovedReason());
		else 
			throw GFX_HR_EXCEPTION(hr);
	}
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
		throw GFX_MSG_EXCEPTION(L"No found DXGI Adapters.");

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

	UINT swapFlags = 0u;
#ifndef NDEBUG
	swapFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	HRESULT hr;
	GFX_ERROR_IF(D3D11CreateDeviceAndSwapChain(
		adapters[0].pAdapter,			// Adapter
		D3D_DRIVER_TYPE_UNKNOWN,		// DriverType
		nullptr,						// Software
		swapFlags,						// Flags
		nullptr,						// FeatureLevels
		0,								// FeatureLevels
		D3D11_SDK_VERSION,				// SDKVersion
		&scd,							// SwapChainDesc
		swapchain.GetAddressOf(),		// SwapChain
		device.GetAddressOf(),			// Device
		nullptr,						// FeatureLevel
		deviceContext.GetAddressOf()	// ImmediateContext
	));

	com_ptr<ID3D11Texture2D> backBuffer;
	GFX_ERROR_IF(swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf())));



	// Render Target
	GFX_ERROR_IF(device->CreateRenderTargetView(backBuffer.Get(), NULL, renderTargetView.GetAddressOf()));
	//GFX_ERROR_IF_MSG(hr, L"Failed to create RenderTargetView.");

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

	GFX_ERROR_IF(device->CreateTexture2D(&depthStencilDesc, NULL, depthStencilBuffer.GetAddressOf()));

	GFX_ERROR_IF(device->CreateDepthStencilView(depthStencilBuffer.Get(), NULL, depthStencilView.GetAddressOf()));

	this->deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());



	// Depth Stencil State
	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
	ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthStencilStateDesc.DepthEnable = true;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
	GFX_ERROR_IF(device->CreateDepthStencilState(&depthStencilStateDesc, depthStencilState.GetAddressOf()));



	// Rasterizer state
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID; // Fill the triangles formed by the vertices. Adjacent vertices are not drawn.
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;	 // Do not draw triangles that are back-facing.
	GFX_ERROR_IF(device->CreateRasterizerState(&rasterizerDesc, rasterizerState.GetAddressOf()));



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
	GFX_ERROR_IF(device->CreateSamplerState(&sampDesc, samplerState.GetAddressOf()));




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


	camera.Initialize(Camera::ProjectionType::Perspective, static_cast<float>(windowWidth), static_cast<float>(windowHeight));

	// Scene
	
	HRESULT hr;
	/*HRESULT hr = vertexBuffer.Initialize(device.Get(), v, ARRAYSIZE(v));
	GFX_ERROR_IF_MSG(hr, L"Failed to create vertex buffer.");

	hr = indexBuffer.Initialize(device.Get(), indices, ARRAYSIZE(indices));
	GFX_ERROR_IF_MSG(hr, L"Failed to create index buffer.");*/

	/*hr = constantBuffer.Initialize(device.Get(), deviceContext.Get());
	GFX_ERROR_IF_MSG(hr, L"Failed to create constant buffer.");*/



	/*hr = DirectX::CreateWICTextureFromFile(device.Get(), L"Data\\Textures\\cat.jpg", nullptr, texture.GetAddressOf());
	GFX_ERROR_IF_MSG(hr, L"Failed to load texture from file.");*/

}