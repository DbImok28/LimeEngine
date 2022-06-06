#pragma once
#include "../Systems/DX11/Texture2DDX11.hpp"
#include <string>

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
		Texture2D(ID3D11Device* device, const std::wstring& filePath, TextureType type, size_t Id);

		Texture2DDX11 renderTexture;
		size_t Id;
	private:
		TextureType type = TextureType::Unknown;
	};
}