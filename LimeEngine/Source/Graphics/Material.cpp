// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Material.hpp"

namespace LimeEngine
{
	MaterialBase::MaterialBase(const ResourcePath& resourcePath, MaterialType type) noexcept : GameResource(resourcePath), type(type) {}

	MaterialType MaterialBase::GetType() const noexcept
	{
		return type;
	}

	std::shared_ptr<MaterialInstance> MaterialBase::GetInstance()
	{
		return std::make_shared<MaterialInstance>(GetRef<MaterialBase>());
	}

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
