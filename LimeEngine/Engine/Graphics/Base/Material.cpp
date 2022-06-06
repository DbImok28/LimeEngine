#include "Material.hpp"

namespace LimeEngine
{
	Material::Material(ID3D11DeviceContext* deviceContext, VertexShader* vertexShader, PixelShader* pixelShader, size_t Id) noexcept : Id(Id), renderMaterial(deviceContext, this, vertexShader, pixelShader) {}

	void Material::SetTextures(std::vector<Texture2D*> textures) noexcept
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
}