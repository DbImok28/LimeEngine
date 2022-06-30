#include "Texture2DDX11.hpp"
#include "../../../Exceptions/GraphicsExceptions.hpp"
#include "../../../Helpers/Paths.hpp"
#include <DirectXTK/WICTextureLoader.h>
#include <DirectXTK/DDSTextureLoader.h>

namespace LimeEngine
{
	Texture2DDX11::Texture2DDX11(const RenderingSystemDX11& renderer, const uint8_t* pData, size_t size)
	{
		// TODO: mipmap
		auto device = renderer.device.Get();
		HRESULT hr;
		GFX_ERROR_IF_MSG(DirectX::CreateWICTextureFromMemory(device, pData, size, texture.GetAddressOf(), textureView.GetAddressOf()), "Failed to create texture from memory.");
	}

	Texture2DDX11::Texture2DDX11(const RenderingSystemDX11& renderer, const std::wstring& filePath)
	{
		auto device = renderer.device.Get();
		HRESULT hr;
		if (Paths::GetFileExtension(filePath) == L".dds")
		{
			hr = DirectX::CreateDDSTextureFromFile(device, filePath.c_str(), texture.GetAddressOf(), textureView.GetAddressOf());
			if (FAILED(hr))
			{
				// TODO: Unloaded texture
			}
			return;
		}
		else
		{
			hr = DirectX::CreateWICTextureFromFile(device, filePath.c_str(), texture.GetAddressOf(), textureView.GetAddressOf());
			if (FAILED(hr))
			{
				// TODO: Unloaded texture
			}
		}
	}

	ID3D11ShaderResourceView* Texture2DDX11::GetView() const noexcept
	{
		return textureView.Get();
	}

	ID3D11ShaderResourceView* const* Texture2DDX11::GetViewAddress() const noexcept
	{
		return textureView.GetAddressOf();
	}
}