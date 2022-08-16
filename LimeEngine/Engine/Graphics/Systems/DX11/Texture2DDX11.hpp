#pragma once
#include <string>
#include "../../Base/Texture2D.hpp"
#include "RendererDX11.hpp"

namespace LimeEngine
{
	class Texture2DDX11 : public Texture2D
	{
	public:
		Texture2DDX11(RendererDX11& renderer, TextureType type, size_t id) noexcept;
		Texture2DDX11(RendererDX11& renderer, const uint8_t* pData, size_t size, TextureType type, size_t id);
		Texture2DDX11(RendererDX11& renderer, const std::wstring& filePath, TextureType type, size_t id);

		void Initialize(const uint8_t* pData, size_t size);
		void Initialize(const std::wstring& filePath);
		virtual void Bind() noexcept override;
		ID3D11ShaderResourceView* GetView() const noexcept;
		ID3D11ShaderResourceView* const* GetViewAddress() const noexcept;

	private:
		RendererDX11& renderer;
		com_ptr<ID3D11Resource> texture = nullptr;
		com_ptr<ID3D11ShaderResourceView> textureView;
	};
}