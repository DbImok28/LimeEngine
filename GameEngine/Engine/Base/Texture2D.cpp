#include "Texture2D.hpp"
#include "../Exceptions/GraphicsExceptions.hpp"
#include "../Helpers/Paths.hpp"
#include <DirectXTK/WICTextureLoader.h>
#include <DirectXTK/DDSTextureLoader.h>

Texture2D::Texture2D(ID3D11Device* device, const uint8_t* pData, size_t size, TextureType type) : type(type)
{
	// TODO: mipmap
	HRESULT hr;
	GFX_ERROR_IF_MSG(
		DirectX::CreateWICTextureFromMemory(device, pData, size, texture.GetAddressOf(), textureView.GetAddressOf()),
		L"Failed to create texture from memory."
	);
}

Texture2D::Texture2D(ID3D11Device* device, const std::wstring& filePath, TextureType type)
{
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

ID3D11ShaderResourceView* Texture2D::GetView()
{
	return textureView.Get();
}

ID3D11ShaderResourceView** Texture2D::GetViewAddress()
{
	return textureView.GetAddressOf();
}