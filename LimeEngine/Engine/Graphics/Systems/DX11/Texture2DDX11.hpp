#pragma once
#include <string>
#include "DirectXDef.hpp"

namespace LimeEngine
{
	class Texture2DDX11
	{
	public:
		Texture2DDX11(ID3D11Device* device, const uint8_t* pData, size_t size);
		Texture2DDX11(ID3D11Device* device, const std::wstring& filePath);
		ID3D11ShaderResourceView* GetView() const noexcept;
		ID3D11ShaderResourceView* const* GetViewAddress() const noexcept;

	private:
		com_ptr<ID3D11Resource> texture = nullptr;
		com_ptr<ID3D11ShaderResourceView> textureView;
	};
}