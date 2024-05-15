// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/Texture2D.hpp"
#include "RendererDX11.hpp"

namespace LimeEngine
{
	class Texture2DDX11 : public Texture2D
	{
	public:
		Texture2DDX11(const ResourcePath& resourcePath, TextureType type) noexcept;
		Texture2DDX11(const ResourcePath& resourcePath, const uint8_t* pData, size_t size, TextureType type);
		Texture2DDX11(const ResourcePath& resourcePath, const FPath& filePath, TextureType type);

		void Initialize(const uint8_t* pData, size_t size);
		void Initialize(const FPath& filePath);
		virtual void Bind(uint slotIndex) noexcept override;
		ID3D11ShaderResourceView* GetView() const noexcept;
		ID3D11ShaderResourceView* const* GetViewAddress() const noexcept;

	private:
		com_ptr<ID3D11Resource> texture = nullptr;
		com_ptr<ID3D11ShaderResourceView> textureView;
	};
}
