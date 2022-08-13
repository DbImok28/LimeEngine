#include "Material.hpp"

namespace LimeEngine
{
	Material::Material(VertexShader* vertexShader, PixelShader* pixelShader, MaterialType type, size_t id) noexcept :
		id(id), vertexShader(vertexShader), pixelShader(pixelShader), type(type)
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

	void Material::ApplyMaterial(const RenderingSystemDX11& renderer) noexcept
	{
		vertexShader->Bind();
		pixelShader->Bind();
		for (auto& texture : GetTextures())
		{
			texture->Bind();
		}
	}
}