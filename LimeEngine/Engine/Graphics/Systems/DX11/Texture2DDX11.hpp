#pragma once
#include <string>
#include "RenderingSystemDX11.hpp"

namespace LimeEngine
{
	class Texture2DDX11
	{
	public:
		Texture2DDX11(const RenderingSystemDX11& renderer, const uint8_t* pData, size_t size);
		Texture2DDX11(const RenderingSystemDX11& renderer, const std::wstring& filePath);
		ID3D11ShaderResourceView* GetView() const noexcept;
		ID3D11ShaderResourceView* const* GetViewAddress() const noexcept;

	private:
		com_ptr<ID3D11Resource> texture = nullptr;
		com_ptr<ID3D11ShaderResourceView> textureView;
	};
}