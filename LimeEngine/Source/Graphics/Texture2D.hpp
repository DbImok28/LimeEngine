// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "IBindable.hpp"
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

	class Texture2D : public GameResource
	{
	public:
		static URef<Texture2D> Create(const ResourcePath& resourcePath, TextureType type);
		static URef<Texture2D> Create(const ResourcePath& resourcePath, const uint8_t* pData, size_t size, TextureType type);
		static URef<Texture2D> Create(const ResourcePath& resourcePath, const FPath& filePath, TextureType type);

		Texture2D(const ResourcePath& resourcePath, TextureType type) noexcept;

		virtual void Bind(uint slotIndex) noexcept = 0;

	protected:
		TextureType type;
	};
}