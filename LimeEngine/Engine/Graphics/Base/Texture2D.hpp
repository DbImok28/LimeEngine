#pragma once
#include <string>
#include "IBindable.hpp"

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

	class Texture2D : public IBindable
	{
	public:
		Texture2D(TextureType type, size_t id) noexcept;
		size_t GetID() const noexcept;

	protected:
		TextureType type;

	private:
		size_t id;
	};
}