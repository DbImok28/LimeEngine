// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Texture2DDX11.hpp"
#include "ShadersDX11.hpp"
#include "ExceptionsDX11.hpp"
#include <stb_image.h>

namespace LimeEngine
{
	Texture2DDX11::Texture2DDX11(const ResourcePath& resourcePath, TextureType type) noexcept : Texture2D(resourcePath, type) {}

	Texture2DDX11::Texture2DDX11(const ResourcePath& resourcePath, const uint8_t* pData, size_t size, TextureFormat format, TextureType type) : Texture2DDX11(resourcePath, type)
	{
		LoadTextureFromMemory(pData, size, format);
	}

	Texture2DDX11::Texture2DDX11(const ResourcePath& resourcePath, const FPath& filePath, TextureFormat format, TextureType type) : Texture2DDX11(resourcePath, type)
	{
		LoadTextureFromFile(filePath, format);
	}

	Texture2DDX11::Texture2DDX11(const ResourcePath& resourcePath, ID3D11Texture2D* texture, ID3D11ShaderResourceView* textureView, TextureType type) :
		texture(texture), textureView(textureView), Texture2D(resourcePath, type)
	{
		UpdateTextureInfo();
	}

	void Texture2DDX11::LoadTextureFromMemory(const uint8_t* data, size_t size, TextureFormat format)
	{
		int stbiFormat = 0;
		switch (format)
		{
			case TextureFormat::R8:
			{
				stbiFormat = STBI_grey;
				break;
			}
			case TextureFormat::RG8:
			{
				stbiFormat = STBI_grey_alpha;
				break;
			}
			case TextureFormat::RGBA8:
			{
				stbiFormat = STBI_rgb_alpha;
				break;
			}
			default: break;
		}

		int width, height, sourceChannelCount;
		stbi_uc* imageData = stbi_load_from_memory(data, size, &width, &height, &sourceChannelCount, stbiFormat);
		if (!imageData)
		{
			LE_CORE_ASSERT(false, "Failed to load image from memory. STBImage error reason: {}", stbi_failure_reason());
			return;
		}

		try
		{
			CreateTextureFromRawData(imageData, width, height, format);
		}
		catch (const std::exception& e)
		{
			LE_CORE_ASSERT(false, "Failed to load image from memory. {}", e.what());
		}
		stbi_image_free(imageData);
	}

	void Texture2DDX11::LoadTextureFromFile(const FPath& filePath, TextureFormat format)
	{
		int stbiFormat = 0;
		switch (format)
		{
			case TextureFormat::R8:
			{
				stbiFormat = STBI_grey;
				break;
			}
			case TextureFormat::RG8:
			{
				stbiFormat = STBI_grey_alpha;
				break;
			}
			case TextureFormat::RGBA8:
			{
				stbiFormat = STBI_rgb_alpha;
				break;
			}
			default: break;
		}

		int width, height, sourceChannelCount;
		stbi_uc* imageData = stbi_load(filePath.string().c_str(), &width, &height, &sourceChannelCount, stbiFormat);
		if (!imageData)
		{
			LE_CORE_ASSERT(false, "Failed to load image from file: {}. STBImage error reason: {}", filePath.string().c_str(), stbi_failure_reason());
			return;
		}

		try
		{
			CreateTextureFromRawData(imageData, width, height, format);
		}
		catch (const std::exception& e)
		{
			LE_CORE_ASSERT(false, "Failed to load image from file: {}. {}", filePath.string().c_str(), e.what());
		}
		stbi_image_free(imageData);
	}

	void Texture2DDX11::CreateTextureFromRawData(const uint8_t* data, uint width, uint height, TextureFormat format)
	{
		DXGI_FORMAT dxgiFormat = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
		int channelCount = 0;

		switch (format)
		{
			case TextureFormat::R8:
			{
				dxgiFormat = DXGI_FORMAT::DXGI_FORMAT_R8_UNORM;
				channelCount = 1;
				break;
			}
			case TextureFormat::RG8:
			{
				dxgiFormat = DXGI_FORMAT::DXGI_FORMAT_R8G8_UNORM;
				channelCount = 2;
				break;
			}
			case TextureFormat::RGBA8:
			{
				dxgiFormat = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
				channelCount = 4;
				break;
			}
			default: break;
		}
		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = dxgiFormat;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA subresourceData = {};
		subresourceData.pSysMem = data;
		subresourceData.SysMemPitch = width * channelCount;
		subresourceData.SysMemSlicePitch = width * height * channelCount;
		GFX_CHECK_HR(device->CreateTexture2D(&textureDesc, &subresourceData, texture.GetAddressOf()));

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = textureDesc.Format;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = textureDesc.MipLevels;
		GFX_CHECK_HR(device->CreateShaderResourceView(texture.Get(), &srvDesc, textureView.GetAddressOf()));
		UpdateTextureInfo();
	}

	void Texture2DDX11::UpdateTextureInfo()
	{
		if (texture)
		{
			D3D11_TEXTURE2D_DESC textureDesc;
			texture->GetDesc(&textureDesc);

			D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
			textureView->GetDesc(&viewDesc);

			format = DXGIFormatToShaderDataType(viewDesc.Format);

			width = textureDesc.Width;
			height = textureDesc.Height;

			mipLevels = textureDesc.MipLevels;
			arraySize = textureDesc.ArraySize;
		}
	}

	void Texture2DDX11::Bind(uint slotIndex) noexcept
	{
		// TODO:Add default texture
		if (textureView)
		{
			auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
			deviceContext->PSSetShaderResources(slotIndex, 1u, textureView.GetAddressOf());
		}
	}

	URef<Texture2D> Texture2DDX11::Clone(const ResourcePath& cloneResourcePath)
	{
		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();

		D3D11_TEXTURE2D_DESC textureDesc;
		texture->GetDesc(&textureDesc);

		ID3D11Texture2D* textureCopy = nullptr;
		GFX_CHECK_HR(device->CreateTexture2D(&textureDesc, nullptr, &textureCopy));

		deviceContext->CopyResource(textureCopy, texture.Get());

		D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
		textureView->GetDesc(&viewDesc);

		ID3D11ShaderResourceView* textureViewCopy;
		GFX_CHECK_HR(device->CreateShaderResourceView(textureCopy, &viewDesc, &textureViewCopy));

		return MakeUnique<Texture2DDX11>(cloneResourcePath, textureCopy, textureViewCopy, type);
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
