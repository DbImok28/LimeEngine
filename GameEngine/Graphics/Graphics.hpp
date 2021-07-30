#pragma once
#include "DirectXDef.hpp"
#include <DirectXTK/WICTextureLoader.h>
#include <vector>
#include <string>
#include <sstream>
#include "../Exceptions/EngineExceptions.hpp"
#include "../Helpers/Paths.hpp"
#include "Shaders.hpp"
#include "Vertex.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#define GFX_EXCEPTION(hr) Graphics::GraphicsHrException(__LINE__, __FILE__, hr)
#define GFX_THROW_EXCEPTION_IF(hr) if(FAILED(hr)) throw Graphics::GraphicsHrException(__LINE__, __FILE__, hr)

#define GFX_INFO_HR_EXCEPTION(hr, info) Graphics::InfoGraphicsHrException(__LINE__, __FILE__, hr, info)
#define GFX_THROW_INFO_HR_EXCEPTION_IF(hr, info) if(FAILED(hr)) throw Graphics::InfoGraphicsHrException(__LINE__, __FILE__, hr, info)

#define GFX_INFO_EXCEPTION(info) Graphics::InfoGraphicsException(__LINE__, __FILE__, info)

#define GFX_ERROR_IF(hr, info) GFX_THROW_INFO_HR_EXCEPTION_IF(hr, info)

class Graphics
{
public:
	class GraphicsHrException : public HrException
	{
	public:
		GraphicsHrException(int line, const char* file, HRESULT hr) noexcept;
		const wchar_t* GetType() const noexcept override;
	};

	class InfoGraphicsHrException : public GraphicsHrException
	{
	public:
		InfoGraphicsHrException(int line, const char* file, HRESULT hr, std::wstring info) noexcept;
		InfoGraphicsHrException(int line, const char* file, HRESULT hr, std::vector<std::wstring> info) noexcept;
		const wchar_t* GetType() const noexcept override;
		const wchar_t* what() const noexcept override;
	private:
		std::wstring info;
	};

	class InfoGraphicsException : public EngineException
	{
	public:
		InfoGraphicsException(int line, const char* file, std::wstring info) noexcept;
		InfoGraphicsException(int line, const char* file, std::vector<std::wstring> info) noexcept;
		const wchar_t* GetType() const noexcept override;
		const wchar_t* what() const noexcept override;
	private:
		std::wstring info;
	};
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

	int windowWidth = 0;
	int windowHeight = 0;
};