// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Shaders.hpp"
#include "Base/GameResource.hpp"

namespace LimeEngine
{
	enum class TextureType
	{
		Diffuse,
		Specular,
		Roughness,
		Emissive,
		Height,
		Mask,
		Normal,
		Opacity,
		Displacement,
		Reflection,
		LightMap,
		Unknown
	};

	enum class TextureFormat
	{
		R8,
		RG8,
		RGBA8,
		Unknown
	};

	std::string TextureFormatToString(TextureFormat format) noexcept;

	class Texture2D : public GameResource
	{
	public:
		static URef<Texture2D> Create(const ResourcePath& resourcePath, TextureType type);
		static URef<Texture2D> Create(const ResourcePath& resourcePath, const uint8_t* pData, size_t size, TextureFormat format, TextureType type);
		static URef<Texture2D> Create(const ResourcePath& resourcePath, const FPath& filePath, TextureFormat format, TextureType type);

		Texture2D(const ResourcePath& resourcePath, TextureType type) noexcept;

		virtual void Bind(uint slotIndex) noexcept = 0;
		virtual URef<Texture2D> Clone(const ResourcePath& cloneResourcePath) = 0;

		ShaderDataType GetFormat() const noexcept
		{
			return format;
		}
		UIntVector2D GetSize() const noexcept
		{
			return { width, height };
		}
		uint32 GetWidth() const noexcept
		{
			return width;
		}
		uint32 GetHeight() const noexcept
		{
			return height;
		}
		uint GetMipLevels() const noexcept
		{
			return mipLevels;
		}
		uint ArraySize() const noexcept
		{
			return arraySize;
		}
		virtual void* GetView() const = 0;

	protected:
		TextureType type;
		ShaderDataType format;

		uint32 width = 0u;
		uint32 height = 0u;

		uint mipLevels = 0u;
		uint arraySize = 0u;
	};
}