#include "Material.hpp"

namespace LimeEngine
{
	Material::Material(VertexShader* vertexShader, PixelShader* pixelShader, size_t id) noexcept : id(id), vertexShader(vertexShader), pixelShader(pixelShader) {}

	void Material::SetTextures(const std::vector<Texture2D*>& textures) noexcept
	{
		this->textures = textures;
	}

	void Material::AddTexture(Texture2D* texture) noexcept
	{
		this->textures.push_back(texture);
	}

	const std::vector<Texture2D*>& Material::GetTextures() const noexcept
	{
		return textures;
	}

	void Material::ApplyMaterial(const RenderingSystemDX11* renderer) const noexcept
	{
		auto deviceContext = renderer->deviceContext.Get();

		deviceContext->IASetInputLayout(vertexShader->GatInputLoyout());
		deviceContext->VSSetShader(vertexShader->GetShader(), NULL, 0);
		deviceContext->PSSetShader(pixelShader->GetShader(), NULL, 0);
		for (auto& texture : GetTextures())
		{
			deviceContext->PSSetShaderResources(0, 1, texture->GetViewAddress());
		}
	}
}