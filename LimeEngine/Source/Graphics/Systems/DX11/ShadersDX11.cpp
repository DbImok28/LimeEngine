#include "ShadersDX11.hpp"
#include "Exceptions/GraphicsExceptions.hpp"
#include "Helpers/StringHelper.hpp"
#include "Graphics/Base/Material.hpp"
#include <sstream>

namespace LimeEngine
{
	VertexShaderDX11::VertexShaderDX11(RendererDX11& renderer) noexcept : BindableDX11(renderer) {}

	VertexShaderDX11::VertexShaderDX11(RendererDX11& renderer, const std::wstring& filePath, MaterialType materialType) : BindableDX11(renderer)
	{
		Initialize(filePath, materialType);
	}

	void VertexShaderDX11::Initialize(const std::wstring& filePath, MaterialType materialType)
	{
		HRESULT hr = D3DReadFileToBlob(filePath.c_str(), shaderBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			std::ostringstream oss;
			oss << "Failed to load vertex shader: " << StringHelper::StringToChar8(filePath);
			throw GFX_EXCEPTION_HR_MSG(hr, oss.str());
		}
		hr = GetDevice()->CreateVertexShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, shader.GetAddressOf());
		if (FAILED(hr))
		{
			std::ostringstream oss;
			oss << "Failed to create vertex shader: " << StringHelper::StringToChar8(filePath);
			throw GFX_EXCEPTION_HR_MSG(hr, oss.str());
		}

		auto loyout = MakeInputLayout(materialType);
		GFX_CHECK_HR_MSG(
			GetDevice()->CreateInputLayout(
				loyout.data(), static_cast<uint>(loyout.size()), shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), inputLoyout.GetAddressOf()),
			"Failed to create InputLayout.");
	}

	std::vector<D3D11_INPUT_ELEMENT_DESC> VertexShaderDX11::MakeInputLayout(MaterialType materialType) const
	{
		switch (materialType)
		{
			case MaterialType::Solid:
				return {
					{"POSITION",  0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,                            D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
					{ "NORMAL",   0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
					{ "TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
				};
			default: throw GFX_EXCEPTION_MSG("This material type is not supported.");
		}
	}

	ID3D11VertexShader* VertexShaderDX11::GetShader() const noexcept
	{
		return shader.Get();
	}

	ID3D10Blob* VertexShaderDX11::GetBuffer() const noexcept
	{
		return shaderBuffer.Get();
	}

	ID3D11InputLayout* VertexShaderDX11::GatInputLoyout() const noexcept
	{
		return inputLoyout.Get();
	}

	void VertexShaderDX11::Bind() noexcept
	{
		GetDeviceContext()->IASetInputLayout(GatInputLoyout());
		GetDeviceContext()->VSSetShader(GetShader(), NULL, 0);
	}

	// --

	PixelShaderDX11::PixelShaderDX11(RendererDX11& renderer) noexcept : BindableDX11(renderer) {}

	PixelShaderDX11::PixelShaderDX11(RendererDX11& renderer, const std::wstring& filePath) : BindableDX11(renderer)
	{
		Initialize(filePath);
	}

	void PixelShaderDX11::Initialize(const std::wstring& filePath)
	{
		HRESULT hr = D3DReadFileToBlob(filePath.c_str(), shaderBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			std::stringstream oss;
			oss << "Failed to load pixel shader: " << StringHelper::StringToChar8(filePath);
			throw GFX_EXCEPTION_HR_MSG(hr, oss.str());
		}
		hr = GetDevice()->CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, shader.GetAddressOf());
		if (FAILED(hr))
		{
			std::stringstream oss;
			oss << "Failed to create pixel shader: " << StringHelper::StringToChar8(filePath);
			throw GFX_EXCEPTION_HR_MSG(hr, oss.str());
		}
	}

	void PixelShaderDX11::Bind() noexcept
	{
		GetDeviceContext()->PSSetShader(GetShader(), NULL, 0);
	}

	ID3D11PixelShader* PixelShaderDX11::GetShader() const noexcept
	{
		return shader.Get();
	}

	ID3D10Blob* PixelShaderDX11::GetBuffer() const noexcept
	{
		return shaderBuffer.Get();
	}
}