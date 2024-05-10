// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "ShadersDX11.hpp"
#include "ExceptionsDX11.hpp"
#include "Utility/StringUtility.hpp"
#include "Graphics/Material.hpp"

namespace LimeEngine
{
	// VertexShaderDX11

	VertexShaderDX11::VertexShaderDX11() noexcept {}

	VertexShaderDX11::VertexShaderDX11(const FPath& filePath, MaterialType materialType)
	{
		Initialize(filePath, materialType);
	}

	void VertexShaderDX11::Initialize(const FPath& filePath, MaterialType materialType)
	{
		HRESULT hr = D3DReadFileToBlob(filePath.c_str(), shaderBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			std::ostringstream oss;
			oss << "Failed to load vertex shader: " << filePath;
			throw GFX_EXCEPTION_HR_MSG(hr, oss.str());
		}
		auto loyout = MakeInputLayout(materialType);
		Renderer::GetRenderer<RendererDX11>().context.CreateVertexShader(
			loyout.data(), static_cast<uint>(loyout.size()), shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), inputLoyout.GetAddressOf(), shader.GetAddressOf());
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

	ID3D11InputLayout* VertexShaderDX11::GetInputLoyout() const noexcept
	{
		return inputLoyout.Get();
	}

	void VertexShaderDX11::Bind() noexcept
	{
		auto& context = Renderer::GetRenderer<RendererDX11>().context;
		context.SetInputLayout(GetInputLoyout());
		context.SetVertexShader(GetShader());
	}

	// PixelShaderDX11

	PixelShaderDX11::PixelShaderDX11() noexcept {}

	PixelShaderDX11::PixelShaderDX11(const FPath& filePath)
	{
		Initialize(filePath);
	}

	void PixelShaderDX11::Initialize(const FPath& filePath)
	{
		HRESULT hr = D3DReadFileToBlob(filePath.c_str(), shaderBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			std::stringstream oss;
			oss << "Failed to load pixel shader: " << filePath;
			throw GFX_EXCEPTION_HR_MSG(hr, oss.str());
		}
		Renderer::GetRenderer<RendererDX11>().context.CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), shader.GetAddressOf());
	}

	void PixelShaderDX11::Bind() noexcept
	{
		Renderer::GetRenderer<RendererDX11>().context.SetPixelShader(GetShader());
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
