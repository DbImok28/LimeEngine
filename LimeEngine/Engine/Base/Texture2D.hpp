#pragma once
#include <string>
#include "../Graphics/DirectXDef.hpp"

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
		Texture2D(ID3D11Device* device, const uint8_t* pData, size_t size, TextureType type);
		Texture2D(ID3D11Device* device, const std::wstring& filePath, TextureType type);
		ID3D11ShaderResourceView* GetView();
		ID3D11ShaderResourceView** GetViewAddress();
	private:
		com_ptr<ID3D11Resource> texture = nullptr;
		com_ptr<ID3D11ShaderResourceView> textureView = nullptr;
		TextureType type = TextureType::Unknown;
	};
}