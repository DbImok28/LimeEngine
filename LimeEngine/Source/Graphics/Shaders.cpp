// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Shaders.hpp"
#include "RenderAPI.hpp"

#if defined(LE_ENABLE_RENDER_API_DX11)
	#include "API/DX11/ShadersDX11.hpp"
#endif

namespace LimeEngine
{
	URef<VertexShader> VertexShader::Create(const FPath& filePath, const InputLayout& inputLayout)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return MakeUnique<VertexShaderDX11>(filePath, inputLayout);
#endif
			default: break;
		}
		LE_ASSERT(false, "Unknown render API. Failed to create VertexShader");
		return nullptr;
	}

	URef<PixelShader> PixelShader::Create(const FPath& filePath)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return MakeUnique<PixelShaderDX11>(filePath);
#endif
			default: break;
		}
		LE_ASSERT(false, "Unknown render API. Failed to create PixelShader");
		return nullptr;
	}

	std::string ShaderDataTypeToString(ShaderDataType dataType) noexcept
	{
		switch (dataType)
		{
			case ShaderDataType::R8: return "R8";
			case ShaderDataType::RG8: return "RG8";
			case ShaderDataType::RGBA8: return "RGBA8";
			case ShaderDataType::RGBA8_SRGB: return "RGBA8_SRGB";
			case ShaderDataType::R16F: return "R16F";
			case ShaderDataType::RG16F: return "RG16F";
			case ShaderDataType::RGBA16F: return "RGBA16F";
			case ShaderDataType::R32F: return "R32F";
			case ShaderDataType::RG32F: return "RG32F";
			case ShaderDataType::RGB32F: return "RGB32F";
			case ShaderDataType::RGBA32F: return "RGBA32F";
			case ShaderDataType::RGB10A2: return "RGB10A2";
			case ShaderDataType::RGB10_XR_BIAS_A2: return "RGB10_XR_BIAS_A2";
			case ShaderDataType::BGRA8: return "BGRA8";
			case ShaderDataType::BGRA8_SRGB: return "BGRA8_SRGB";
			default: return "Unknown";
		}
	}

	ShaderArray::ShaderArray(const InputLayout& inputLayout, const FPath& directoryPath, const std::string& name)
	{
		Load(inputLayout, directoryPath, name);
	}

	void ShaderArray::Load(const InputLayout& inputLayout, const FPath& directoryPath, const std::string& name)
	{
		Add(VertexShader::Create(directoryPath / (name + "_vs.cso"), inputLayout));
		Add(PixelShader::Create(directoryPath / (name + "_ps.cso")));
	}

	void ShaderArray::Add(URef<IBindable>&& shader)
	{
		shaders.push_back(std::move(shader));
	}

	void ShaderArray::Bind()
	{
		for (auto& shader : shaders)
		{
			shader->Bind();
		}
	}
}
