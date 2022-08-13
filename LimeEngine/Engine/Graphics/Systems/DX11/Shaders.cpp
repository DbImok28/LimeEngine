#include "Shaders.hpp"
#include "../../../Exceptions/GraphicsExceptions.hpp"
#include "../../../Helpers/StringHelper.hpp"
#include "../../Base/Material.hpp"
#include <sstream>

namespace LimeEngine
{
	VertexShader::VertexShader(RenderingSystemDX11& renderingSystem) noexcept : BindableDX11(renderingSystem) {}

	void VertexShader::Initalize(std::wstring shaderpath, MaterialType materialType)
	{
		HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), shaderBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			std::ostringstream oss;
			oss << "Failed to load vertex shader: " << StringHelper::StringToChar8(shaderpath);
			throw GFX_EXCEPTION_HR_MSG(hr, oss.str());
		}
		hr = GetDevice()->CreateVertexShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, shader.GetAddressOf());
		if (FAILED(hr))
		{
			std::ostringstream oss;
			oss << "Failed to create vertex shader: " << StringHelper::StringToChar8(shaderpath);
			throw GFX_EXCEPTION_HR_MSG(hr, oss.str());
		}

		auto loyout = MakeInputLayout(materialType);
		GFX_CHECK_HR_MSG(
			GetDevice()->CreateInputLayout(loyout.data(), loyout.size(), shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), inputLoyout.GetAddressOf()),
			"Failed to create InputLayout.");
	}

	std::vector<D3D11_INPUT_ELEMENT_DESC> VertexShader::MakeInputLayout(MaterialType materialType) const
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

	ID3D11VertexShader* VertexShader::GetShader() const noexcept
	{
		return shader.Get();
	}

	ID3D10Blob* VertexShader::GetBuffer() const noexcept
	{
		return shaderBuffer.Get();
	}

	ID3D11InputLayout* VertexShader::GatInputLoyout() const noexcept
	{
		return inputLoyout.Get();
	}

	void VertexShader::Bind() noexcept
	{
		GetDeviceContext()->IASetInputLayout(GatInputLoyout());
		GetDeviceContext()->VSSetShader(GetShader(), NULL, 0);
	}

	// --

	PixelShader::PixelShader(RenderingSystemDX11& renderingSystem) noexcept : BindableDX11(renderingSystem) {}

	void PixelShader::Initalize(std::wstring shaderpath)
	{
		HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), shaderBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			std::stringstream oss;
			oss << "Failed to load pixel shader: " << StringHelper::StringToChar8(shaderpath);
			throw GFX_EXCEPTION_HR_MSG(hr, oss.str());
		}
		hr = GetDevice()->CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, shader.GetAddressOf());
		if (FAILED(hr))
		{
			std::stringstream oss;
			oss << "Failed to create pixel shader: " << StringHelper::StringToChar8(shaderpath);
			throw GFX_EXCEPTION_HR_MSG(hr, oss.str());
		}
	}

	void PixelShader::Bind() noexcept
	{
		GetDeviceContext()->PSSetShader(GetShader(), NULL, 0);
	}

	ID3D11PixelShader* PixelShader::GetShader() const noexcept
	{
		return shader.Get();
	}

	ID3D10Blob* PixelShader::GetBuffer() const noexcept
	{
		return shaderBuffer.Get();
	}
}