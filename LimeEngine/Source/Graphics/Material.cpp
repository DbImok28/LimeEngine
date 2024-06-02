// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Material.hpp"

namespace LimeEngine
{
	SRef<Material> MaterialAsset::Instantiate()
	{
		return MakeUnique<Material>(GetRef<MaterialAsset>());
	}

	void Material::ApplyMaterial() noexcept
	{
		asset->vertexShader->Bind();
		asset->pixelShader->Bind();
		parameters.Bind();
		// TODO: add slot count check
		uint slotIndex = 0;
		for (auto& texture : textures)
		{
			texture->Bind(slotIndex++);
		}
	}

	void Material::SetTextureParameter(const GameResourceRef<Texture2D>& texture, uint slotIndex) noexcept
	{
		if (slotIndex >= textures.size())
		{
			textures.resize(slotIndex + 1u);
		}
		textures[slotIndex] = texture;
	}

	GameResourceRef<Texture2D> Material::GetTextureParameter(uint slotIndex) noexcept
	{
		if (slotIndex > textures.size()) return GameResourceRef<Texture2D>::NullRef();
		return textures[slotIndex];
	}
}
