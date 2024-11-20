// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "ShadersDX11.hpp"
#include "ExceptionsDX11.hpp"
#include "Utility/StringUtility.hpp"

namespace LimeEngine
{
	///////////////////////////////////////////////// InputLayout

	DXGI_FORMAT ShaderDataTypeToDXGIFormat(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::R8: return DXGI_FORMAT::DXGI_FORMAT_R8_UNORM;
			case ShaderDataType::RG8: return DXGI_FORMAT::DXGI_FORMAT_R8G8_UNORM;
			case ShaderDataType::RGBA8: return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
			case ShaderDataType::RGBA8_SRGB: return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
			case ShaderDataType::R16F: return DXGI_FORMAT::DXGI_FORMAT_R16_FLOAT;
			case ShaderDataType::RG16F: return DXGI_FORMAT::DXGI_FORMAT_R16G16_FLOAT;
			case ShaderDataType::RGBA16F: return DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_FLOAT;
			case ShaderDataType::R32F: return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
			case ShaderDataType::RG32F: return DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
			case ShaderDataType::RGB32F: return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
			case ShaderDataType::RGBA32F: return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
			case ShaderDataType::RGB10A2: return DXGI_FORMAT::DXGI_FORMAT_R10G10B10A2_UNORM;
			case ShaderDataType::RGB10_XR_BIAS_A2: return DXGI_FORMAT::DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
			case ShaderDataType::BGRA8: return DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;
			case ShaderDataType::BGRA8_SRGB: return DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
			case ShaderDataType::R24G8: return DXGI_FORMAT::DXGI_FORMAT_X24_TYPELESS_G8_UINT;
		}
		LE_ASSERT(false, "Unknown ShaderDataType");
		return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	}

	ShaderDataType DXGIFormatToShaderDataType(DXGI_FORMAT format)
	{
		switch (format)
		{
			case DXGI_FORMAT::DXGI_FORMAT_R8_UNORM: return ShaderDataType::R8;
			case DXGI_FORMAT::DXGI_FORMAT_R8G8_UNORM: return ShaderDataType::RG8;
			case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM: return ShaderDataType::RGBA8;
			case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM_SRGB: return ShaderDataType::RGBA8_SRGB;
			case DXGI_FORMAT::DXGI_FORMAT_R16_FLOAT: return ShaderDataType::R16F;
			case DXGI_FORMAT::DXGI_FORMAT_R16G16_FLOAT: return ShaderDataType::RG16F;
			case DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_FLOAT: return ShaderDataType::RGBA16F;
			case DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT: return ShaderDataType::R32F;
			case DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT: return ShaderDataType::RG32F;
			case DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT: return ShaderDataType::RGB32F;
			case DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT: return ShaderDataType::RGBA32F;
			case DXGI_FORMAT::DXGI_FORMAT_R10G10B10A2_UNORM: return ShaderDataType::RGB10A2;
			case DXGI_FORMAT::DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM: return ShaderDataType::RGB10_XR_BIAS_A2;
			case DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM: return ShaderDataType::BGRA8;
			case DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM_SRGB: return ShaderDataType::BGRA8_SRGB;
			case DXGI_FORMAT::DXGI_FORMAT_X24_TYPELESS_G8_UINT: return ShaderDataType::R24G8;
		}
		LE_ASSERT(false, "Unknown DXGI_FORMAT");
		return ShaderDataType::None;
	}

	std::vector<D3D11_INPUT_ELEMENT_DESC> ConvertToDX11InputLayout(const InputLayout& inputLayout)
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDX11{};
		inputLayoutDX11.reserve(inputLayout.GetSize());
		bool isFirst = true;
		for (auto& element : inputLayout)
		{
			inputLayoutDX11.push_back({ element.name.c_str(),
										0,
										ShaderDataTypeToDXGIFormat(element.dataType),
										0,
										isFirst ? 0 : D3D11_APPEND_ALIGNED_ELEMENT,
										element.perVertex ? D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA : D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_INSTANCE_DATA,
										0 });
			isFirst = false;
		}
		return inputLayoutDX11;
	}

	///////////////////////////////////////////////// VertexShaderDX11

	VertexShaderDX11::VertexShaderDX11() noexcept {}

	VertexShaderDX11::VertexShaderDX11(const FPath& filePath, const InputLayout& inputLayout)
	{
		Initialize(filePath, inputLayout);
	}

	void VertexShaderDX11::Initialize(const FPath& filePath, const InputLayout& inputLayout)
	{
		this->inputLayout = inputLayout;

		HRESULT hr = D3DReadFileToBlob(filePath.c_str(), shaderBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			std::ostringstream oss;
			oss << "Failed to load vertex shader: " << filePath;
			throw GFX_EXCEPTION_HR_MSG(hr, oss.str());
		}

		auto layout = ConvertToDX11InputLayout(this->inputLayout);
		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();

		GFX_CHECK_HR(device->CreateInputLayout(
			layout.data(), static_cast<uint>(layout.size()), shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), inputLoyoutDX11.GetAddressOf()));
		GFX_CHECK_HR(device->CreateVertexShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, shader.GetAddressOf()));
	}

	ID3D11VertexShader* VertexShaderDX11::GetShader() const noexcept
	{
		return shader.Get();
	}

	ID3D10Blob* VertexShaderDX11::GetBuffer() const noexcept
	{
		return shaderBuffer.Get();
	}

	ID3D11InputLayout* VertexShaderDX11::GetInputLoyoutDX11() const noexcept
	{
		return inputLoyoutDX11.Get();
	}

	void VertexShaderDX11::Bind() noexcept
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->IASetInputLayout(GetInputLoyoutDX11());
		deviceContext->VSSetShader(GetShader(), NULL, 0u);
	}

	///////////////////////////////////////////////// PixelShaderDX11

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

		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();
		device->CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, shader.GetAddressOf());
	}

	void PixelShaderDX11::Bind() noexcept
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->PSSetShader(GetShader(), NULL, 0u);
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
