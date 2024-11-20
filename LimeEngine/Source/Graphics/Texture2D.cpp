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
	URef<Texture2D> Texture2D::Create(const ResourcePath& resourcePath, TextureType type)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return MakeUnique<Texture2DDX11>(resourcePath, type);
#endif
			default: break;
		}
		LE_ASSERT(false, "Unknown render API. Failed to create Texture2D");
		return nullptr;
	}

	URef<Texture2D> Texture2D::Create(const ResourcePath& resourcePath, const uint8_t* pData, size_t size, TextureFormat format, TextureType type)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return MakeUnique<Texture2DDX11>(resourcePath, pData, size, format, type);
#endif
			default: break;
		}
		LE_ASSERT(false, "Unknown render API. Failed to create Texture2D from data");
		return nullptr;
	}

	URef<Texture2D> Texture2D::Create(const ResourcePath& resourcePath, const FPath& filePath, TextureFormat format, TextureType type)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return MakeUnique<Texture2DDX11>(resourcePath, filePath, format, type);
#endif
			default: break;
		}
		LE_ASSERT(false, "Unknown render API. Failed to create Texture2D from file");
		return nullptr;
	}

	Texture2D::Texture2D(const ResourcePath& resourcePath, TextureType type) noexcept : GameResource(resourcePath), type(type) {}

	std::string TextureFormatToString(TextureFormat format) noexcept
	{
		switch (format)
		{
			case TextureFormat::R8: return "R8";
			case TextureFormat::RG8: return "RG8";
			case TextureFormat::RGBA8: return "RGBA8";
			default: return "Unknown";
		}
	}
}