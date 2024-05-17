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
	std::unique_ptr<VertexShader> VertexShader::Create(const FPath& filePath, const InputLayout& inputLayout)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return std::make_unique<VertexShaderDX11>(filePath, inputLayout);
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API. Failed to create VertexShader");
		return nullptr;
	}

	std::unique_ptr<PixelShader> PixelShader::Create(const FPath& filePath)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return std::make_unique<PixelShaderDX11>(filePath);
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API. Failed to create PixelShader");
		return nullptr;
	}

	std::string ShaderDataTypeToString(ShaderDataType dataType) noexcept
	{
		switch (dataType)
		{
			case LimeEngine::ShaderDataType::R8: return "R8";
			case LimeEngine::ShaderDataType::RG8: return "RG8";
			case LimeEngine::ShaderDataType::RGBA8: return "RGBA8";
			case LimeEngine::ShaderDataType::RGBA8_SRGB: return "RGBA8_SRGB";
			case LimeEngine::ShaderDataType::R16F: return "R16F";
			case LimeEngine::ShaderDataType::RG16F: return "RG16F";
			case LimeEngine::ShaderDataType::RGBA16F: return "RGBA16F";
			case LimeEngine::ShaderDataType::R32F: return "R32F";
			case LimeEngine::ShaderDataType::RG32F: return "RG32F";
			case LimeEngine::ShaderDataType::RGB32F: return "RGB32F";
			case LimeEngine::ShaderDataType::RGBA32F: return "RGBA32F";
			case LimeEngine::ShaderDataType::RGB10A2: return "RGB10A2";
			case LimeEngine::ShaderDataType::RGB10_XR_BIAS_A2: return "RGB10_XR_BIAS_A2";
			case LimeEngine::ShaderDataType::BGRA8: return "BGRA8";
			case LimeEngine::ShaderDataType::BGRA8_SRGB: return "BGRA8_SRGB";
			default: return "Unknown";
		}
	}
}
