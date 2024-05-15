// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Texture2D.hpp"
#include "RenderAPI.hpp"

#if defined(LE_ENABLE_RENDER_API_DX11)
	#include "API/DX11/Texture2DDX11.hpp"
#endif

namespace LimeEngine
{
	std::unique_ptr<Texture2D> Texture2D::Create(const ResourcePath& resourcePath, TextureType type)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return std::make_unique<Texture2DDX11>(resourcePath, type);
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API. Failed to create Texture2D");
		return nullptr;
	}

	std::unique_ptr<Texture2D> Texture2D::Create(const ResourcePath& resourcePath, const uint8_t* pData, size_t size, TextureType type)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return std::make_unique<Texture2DDX11>(resourcePath, pData, size, type);
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API. Failed to create Texture2D from data");
		return nullptr;
	}

	std::unique_ptr<Texture2D> Texture2D::Create(const ResourcePath& resourcePath, const FPath& filePath, TextureType type)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return std::make_unique<Texture2DDX11>(resourcePath, filePath, type);
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API. Failed to create Texture2D from file");
		return nullptr;
	}

	Texture2D::Texture2D(const ResourcePath& resourcePath, TextureType type) noexcept : GameResource(resourcePath), type(type) {}
}