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

	class Texture2D : public IBindable, public GameResource
	{
	public:
		Texture2D(const ResourcePath& resourcePath, TextureType type) noexcept;

	protected:
		TextureType type;
	};
}