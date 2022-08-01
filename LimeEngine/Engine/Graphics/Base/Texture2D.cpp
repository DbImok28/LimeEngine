#include "Texture2D.hpp"
#include "../../Exceptions/GraphicsExceptions.hpp"
#include "../../Helpers/Paths.hpp"
#include <DirectXTK/WICTextureLoader.h>
#include <DirectXTK/DDSTextureLoader.h>

namespace LimeEngine
{
	Texture2D::Texture2D(const RenderingSystemDX11* renderer, const uint8_t* pData, size_t size, TextureType type, size_t id) : id(id), type(type)
	{
		// TODO: mipmap
		auto device = renderer->device.Get();
		GFX_CHECK_HR_MSG(DirectX::CreateWICTextureFromMemory(device, pData, size, texture.GetAddressOf(), textureView.GetAddressOf()), "Failed to create texture from memory.");
	}

	Texture2D::Texture2D(const RenderingSystemDX11* renderer, const std::wstring& filePath, TextureType type, size_t id) : id(id), type(type)
	{
		auto device = renderer->device.Get();
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

	ID3D11ShaderResourceView* Texture2D::GetView() const noexcept
	{
		return textureView.Get();
	}

	ID3D11ShaderResourceView* const* Texture2D::GetViewAddress() const noexcept
	{
		return textureView.GetAddressOf();
	}
}