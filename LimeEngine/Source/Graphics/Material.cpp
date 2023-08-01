// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Material.hpp"

namespace LimeEngine
{
	Material::Material(const ResourcePath& resourcePath, MaterialType type) noexcept : GameResource(resourcePath), type(type) {}

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

	MasterMaterial::MasterMaterial(const ResourcePath& resourcePath, IBindable* vertexShader, IBindable* pixelShader, MaterialType type) noexcept :
		Material(resourcePath, type), vertexShader(vertexShader), pixelShader(pixelShader)
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