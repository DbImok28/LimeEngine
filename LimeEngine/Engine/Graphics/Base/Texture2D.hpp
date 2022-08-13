#pragma once
#include <string>
#include "../Systems/DX11/BindableDX11.hpp"

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

	class Texture2D : public BindableDX11
	{
	public:
		Texture2D(RenderingSystemDX11& renderer, size_t id);

		void Initialize(const uint8_t* pData, size_t size, TextureType type = TextureType::Diffuse);
		void Initialize(const std::wstring& filePath, TextureType type = TextureType::Diffuse);
		virtual void Bind() noexcept override;
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