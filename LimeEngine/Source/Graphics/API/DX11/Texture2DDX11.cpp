#include "lepch.hpp"
#include "Texture2DDX11.hpp"
#include "ExceptionsDX11.hpp"
#include "Helpers/Paths.hpp"
#include <DirectXTK/WICTextureLoader.h>
#include <DirectXTK/DDSTextureLoader.h>

namespace LimeEngine
{
	Texture2DDX11::Texture2DDX11(RendererDX11& renderer, const ResourcePath& resourcePath, TextureType type) noexcept : Texture2D(resourcePath, type), renderer(renderer) {}

	Texture2DDX11::Texture2DDX11(RendererDX11& renderer, const ResourcePath& resourcePath, const uint8_t* pData, size_t size, TextureType type) :
		Texture2DDX11(renderer, resourcePath, type)
	{
		Initialize(pData, size);
	}

	Texture2DDX11::Texture2DDX11(RendererDX11& renderer, const ResourcePath& resourcePath, const std::wstring& filePath, TextureType type) :
		Texture2DDX11(renderer, resourcePath, type)
	{
		Initialize(filePath);
	}

	void Texture2DDX11::Initialize(const uint8_t* pData, size_t size)
	{
		auto device = renderer.GetDevice();
		GFX_CHECK_HR_MSG(DirectX::CreateWICTextureFromMemory(device, pData, size, texture.GetAddressOf(), textureView.GetAddressOf()), "Failed to create texture from memory.");
	}

	void Texture2DDX11::Initialize(const std::wstring& filePath)
	{
		auto device = renderer.GetDevice();
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

	void Texture2DDX11::Bind() noexcept
	{
		renderer.GetDeviceContext()->PSSetShaderResources(0, 1, GetViewAddress());
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