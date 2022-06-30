#include "Shaders.hpp"
#include "../../../Exceptions/GraphicsExceptions.hpp"
#include "../../../Helpers/StringHelper.hpp"
#include <sstream>

namespace LimeEngine
{
	void VertexShader::Initalize(com_ptr<ID3D11Device>& device, std::wstring shaderpath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements)
	{
		HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), shaderBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			std::ostringstream oss;
			oss << "Failed to load vertex shader: " << StringHelper::StringToChar8(shaderpath);
			throw GFX_MSG_HR_EXCEPTION(hr, oss.str());
		}
		hr = device->CreateVertexShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, shader.GetAddressOf());
		if (FAILED(hr))
		{
			std::ostringstream oss;
			oss << "Failed to create vertex shader: " << StringHelper::StringToChar8(shaderpath);
			throw GFX_MSG_HR_EXCEPTION(hr, oss.str());
		}
		hr = device->CreateInputLayout(layoutDesc, numElements, shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), inputLoyout.GetAddressOf());
		GFX_ERROR_IF_MSG(hr, "Failed to create InputLayout.");
	}

	ID3D11VertexShader* VertexShader::GetShader() const noexcept
	{
		return shader.Get();
	}

	ID3D10Blob* VertexShader::GetBuffer() const noexcept
	{
		return shaderBuffer.Get();
	}

	ID3D11InputLayout* VertexShader::GatInputLoyout() const noexcept
	{
		return inputLoyout.Get();
	}

	//-----

	void PixelShader::Initalize(com_ptr<ID3D11Device>& device, std::wstring shaderpath)
	{
		HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), shaderBuffer.GetAddressOf());
		if (FAILED(hr))
		{
			std::stringstream oss;
			oss << "Failed to load pixel shader: " << StringHelper::StringToChar8(shaderpath);
			throw GFX_MSG_HR_EXCEPTION(hr, oss.str());
		}
		hr = device->CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, shader.GetAddressOf());
		if (FAILED(hr))
		{
			std::stringstream oss;
			oss << "Failed to create pixel shader: " << StringHelper::StringToChar8(shaderpath);
			throw GFX_MSG_HR_EXCEPTION(hr, oss.str());
		}
	}

	ID3D11PixelShader* PixelShader::GetShader() const noexcept
	{
		return shader.Get();
	}

	ID3D10Blob* PixelShader::GetBuffer() const noexcept
	{
		return shaderBuffer.Get();
	}
}