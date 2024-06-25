// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/Texture2D.hpp"
#include "RenderAPIDX11.hpp"

namespace LimeEngine
{
	class Texture2DDX11 : public Texture2D
	{
	public:
		Texture2DDX11(const ResourcePath& resourcePath, TextureType type) noexcept;
		Texture2DDX11(const ResourcePath& resourcePath, const uint8_t* pData, size_t size, TextureFormat format, TextureType type);
		Texture2DDX11(const ResourcePath& resourcePath, const FPath& filePath, TextureFormat format, TextureType type);
		Texture2DDX11(const ResourcePath& resourcePath, ID3D11Texture2D* texture, ID3D11ShaderResourceView* textureView, TextureType type);

		void LoadTextureFromMemory(const uint8_t* data, size_t size, TextureFormat format);
		void LoadTextureFromFile(const FPath& filePath, TextureFormat format);
		void CreateTextureFromRawData(const uint8_t* data, uint width, uint height, TextureFormat format);
		bool TryCreateTextureFromRawData(const uint8_t* data, uint width, uint height, TextureFormat format);
		void UpdateTextureInfo();

		virtual void Bind(uint slotIndex) noexcept override;
		virtual URef<Texture2D> Clone(const ResourcePath& cloneResourcePath) override;

		ID3D11ShaderResourceView* GetView() const noexcept;
		ID3D11ShaderResourceView* const* GetViewAddress() const noexcept;

	protected:
		com_ptr<ID3D11Texture2D> texture = nullptr;
		com_ptr<ID3D11ShaderResourceView> textureView;
	};
}
