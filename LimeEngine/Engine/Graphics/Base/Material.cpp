#include "Material.hpp"

namespace LimeEngine
{
	Material::Material(std::string path, MaterialType type) noexcept : GameResource(path), type(type) {}

	void Material::AddTexture(GameResourceRef<Texture2D> texture) noexcept
	{
		textures.push_back(texture);
	}

	const std::vector<GameResourceRef<Texture2D>>& Material::GetTextures() const noexcept
	{
		return textures;
	}

	void Material::SetTextures(const std::vector<GameResourceRef<Texture2D>>& textures) noexcept
	{
		this->textures = textures;
	}

	MaterialType Material::GetType() const noexcept
	{
		return type;
	}

	MasterMaterial::MasterMaterial(std::string path, IBindable* vertexShader, IBindable* pixelShader, MaterialType type) noexcept :
		Material(path, type), vertexShader(vertexShader), pixelShader(pixelShader)
	{}

	void MasterMaterial::ApplyMaterial() noexcept
	{
		vertexShader->Bind();
		pixelShader->Bind();
		for (auto& texture : textures)
		{
			texture->Bind();
		}
	}
}