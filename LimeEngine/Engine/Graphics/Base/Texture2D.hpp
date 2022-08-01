#pragma once
#include <string>
#include "../Systems/DX11/RenderingSystemDX11.hpp"

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
		Texture2D(const RenderingSystemDX11* renderer, const uint8_t* pData, size_t size, TextureType type, size_t id);
		Texture2D(const RenderingSystemDX11* renderer, const std::wstring& filePath, TextureType type, size_t id);
		ID3D11ShaderResourceView* GetView() const noexcept;
		ID3D11ShaderResourceView* const* GetViewAddress() const noexcept;

	private:
		com_ptr<ID3D11Resource> texture = nullptr;
		com_ptr<ID3D11ShaderResourceView> textureView;
		size_t id;

	private:
		TextureType type = TextureType::Unknown;
	};
}