// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Material.hpp"

namespace LimeEngine
{
	Material::Material(const ResourcePath& resourcePath, MaterialType type) noexcept : GameResource(resourcePath), type(type) {}

	MaterialType Material::GetType() const noexcept
	{
		return type;
	}

	std::shared_ptr<MaterialInstance> Material::GetInstance()
	{
		return std::make_shared<MaterialInstance>(GetRef<Material>());
	}

	// --

	MasterMaterial::MasterMaterial(const ResourcePath& resourcePath, std::unique_ptr<IBindable> vertexShader, std::unique_ptr<IBindable> pixelShader, MaterialType type) noexcept :
		Material(resourcePath, type), vertexShader(std::move(vertexShader)), pixelShader(std::move(pixelShader))
	{}

	void MasterMaterial::ApplyMaterial() noexcept
	{
		vertexShader->Bind();
		pixelShader->Bind();
	}

	// --

	void MaterialInstance::AddTexture(GameResourceRef<Texture2D> texture) noexcept
	{
		textures.push_back(texture);
	}

	const std::vector<GameResourceRef<Texture2D>>& MaterialInstance::GetTextures() const noexcept
	{
		return textures;
	}

	void MaterialInstance::SetTextures(const std::vector<GameResourceRef<Texture2D>>& textures) noexcept
	{
		this->textures = textures;
	}

	void MaterialInstance::ApplyMaterial() noexcept
	{
		material->ApplyMaterial();
		for (auto& texture : textures)
		{
			texture->Bind();
		}
	}
}
