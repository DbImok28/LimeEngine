#include "Texture2D.hpp"
#include "../../Exceptions/GraphicsExceptions.hpp"
#include "../../Helpers/Paths.hpp"
#include <DirectXTK/WICTextureLoader.h>
#include <DirectXTK/DDSTextureLoader.h>

namespace LimeEngine
{
	Texture2D::Texture2D(RenderingSystemDX11& renderer, size_t id) : BindableDX11(renderer), id(id) {}

	void Texture2D::Initialize(const uint8_t* pData, size_t size, TextureType type)
	{
		auto device = GetDevice();
		GFX_CHECK_HR_MSG(DirectX::CreateWICTextureFromMemory(device, pData, size, texture.GetAddressOf(), textureView.GetAddressOf()), "Failed to create texture from memory.");
	}

	void Texture2D::Initialize(const std::wstring& filePath, TextureType type)
	{
		auto device = GetDevice();
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

	void Texture2D::Bind() noexcept
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetViewAddress());
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