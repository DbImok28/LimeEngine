#include "Material.hpp"

namespace LimeEngine
{
	Material::Material(const RenderingSystemDX11& renderer, VertexShader* vertexShader, PixelShader* pixelShader, size_t id) noexcept :
		id(id), renderMaterial(renderer, this, vertexShader, pixelShader)
	{}

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
}