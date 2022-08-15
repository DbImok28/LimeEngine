#include "Material.hpp"

namespace LimeEngine
{
	Material::Material(MaterialType type, size_t id) noexcept : type(type), id(id) {}

	void Material::AddTexture(Texture2D* texture) noexcept
	{
		textures.push_back(texture);
	}

	const std::vector<Texture2D*>& Material::GetTextures() const noexcept
	{
		return textures;
	}

	void Material::SetTextures(const std::vector<Texture2D*>& textures) noexcept
	{
		this->textures = textures;
	}

	MaterialType Material::GetType() const noexcept
	{
		return type;
	}

	size_t Material::GetID() const noexcept
	{
		return id;
	}

	MasterMaterial::MasterMaterial(IBindable* vertexShader, IBindable* pixelShader, MaterialType type, size_t id) noexcept :
		Material(type, id), vertexShader(vertexShader), pixelShader(pixelShader)
	{}

	void MasterMaterial::ApplyMaterial() noexcept
	{
		vertexShader->Bind();
		pixelShader->Bind();
		for (auto& texture : GetTextures())
		{
			texture->Bind();
		}
	}
}