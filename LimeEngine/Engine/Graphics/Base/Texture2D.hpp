#pragma once
#include <string>
#include "../Systems/DX11/Texture2DDX11.hpp"

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

	class Texture2D
	{
	public:
		Texture2D(const RenderingSystemDX11& renderer, const std::wstring& filePath, TextureType type, size_t Id);

		Texture2DDX11 renderTexture;
		size_t Id;
	private:
		TextureType type = TextureType::Unknown;
	};
}