#include "Material.hpp"

namespace LimeEngine
{
	Material::Material(ID3D11DeviceContext* deviceContext, VertexShader* vertexShader, PixelShader* pixelShader) noexcept :
		deviceContext(deviceContext),
		vertexShader(vertexShader),
		pixelShader(pixelShader)
	{
	}

	void Material::SetTextures(std::vector<Texture2D*> textures)
	{
		this->textures = textures;
	}

	void Material::AddTexture(Texture2D* texture)
	{
		this->textures.push_back(texture);
	}

	void Material::Apply() const noexcept
	{
		deviceContext->IASetInputLayout(vertexShader->GatInputLoyout());
		deviceContext->VSSetShader(vertexShader->GetShader(), NULL, 0);
		deviceContext->PSSetShader(pixelShader->GetShader(), NULL, 0);
		for (auto& texture : textures)
		{
			deviceContext->PSSetShaderResources(0, 1, texture->GetViewAddress());
		}
	}
}