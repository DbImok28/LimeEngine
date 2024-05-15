// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Shaders.hpp"
#include "RenderAPI.hpp"
#include "Graphics/Material.hpp"

#if defined(LE_ENABLE_RENDER_API_DX11)
	#include "API/DX11/ShadersDX11.hpp"
#endif

namespace LimeEngine
{
	std::unique_ptr<VertexShader> VertexShader::Create(const FPath& filePath, MaterialType materialType)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return std::make_unique<VertexShaderDX11>(filePath, materialType);
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
}
