#pragma once
#include "DirectXDef.hpp"
#include "../Exceptions/GraphicsExceptions.hpp"
#include "../Helpers/Paths.hpp"
#include <DirectXTK/WICTextureLoader.h>
#include <vector>
#include <string>
#include <sstream>
#include "Shaders.hpp"
#include "../Base/Vertex.hpp"
#include "Buffers/VertexBuffer.hpp"
#include "Buffers/IndexBuffer.hpp"
#include "Buffers/ConstantBuffer.hpp"

class Graphics
{
public:
	Graphics(HWND hWnd, int width, int height);
	void RenderFrame();
private:
	void PreProcessing();
	void Processing();
	void PostProcessing();

	void InitializeDirectX(HWND hWnd);
	void Initialize();

	com_ptr<ID3D11Device> device;
	com_ptr<ID3D11DeviceContext> deviceContext;
	com_ptr<IDXGISwapChain> swapchain;
	com_ptr<ID3D11RenderTargetView> renderTargetView;

	com_ptr<ID3D11DepthStencilView> depthStencilView;
	com_ptr<ID3D11Texture2D> depthStencilBuffer;
	com_ptr<ID3D11DepthStencilState> depthStencilState;

	com_ptr<ID3D11RasterizerState> rasterizerState;

	VertexShader vertexShader;
	PixelShader pixelShader;

	com_ptr<ID3D11SamplerState> samplerState;
	com_ptr<ID3D11ShaderResourceView> texture;

	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	ConstantBuffer<CB_VS_VertexShader> constantBuffer;

	int windowWidth = 0;
	int windowHeight = 0;
};