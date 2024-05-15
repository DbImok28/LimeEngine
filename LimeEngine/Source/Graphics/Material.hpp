// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Texture2D.hpp"
#include "Base/GameResource.hpp"
#include "Shaders.hpp"

namespace LimeEngine
{
	enum class MaterialType
	{
		Unknown,
		Solid
	};

	class Material;

	// Material Template
	class MaterialAsset : public GameResource
	{
		LE_DELETE_COPY(MaterialAsset)

	public:
		MaterialAsset(const ResourcePath& resourcePath, std::unique_ptr<VertexShader>&& vertexShader, std::unique_ptr<PixelShader>&& pixelShader, MaterialType type) noexcept :
			GameResource(resourcePath), type(type), vertexShader(std::move(vertexShader)), pixelShader(std::move(pixelShader))
		{}

		std::shared_ptr<Material> Instantiate();

	public:
		MaterialType type;

		std::unique_ptr<VertexShader> vertexShader;
		std::unique_ptr<PixelShader> pixelShader;
	};

	class Material
	{
		LE_DELETE_COPY(Material)

	public:
		Material(const GameResourceRef<MaterialAsset>& asset) noexcept : asset(asset) {}

		void ApplyMaterial() noexcept;

		void SetTextureParameter(const GameResourceRef<Texture2D>& texture, uint slotIndex) noexcept;
		GameResourceRef<Texture2D> GetTextureParameter(uint slotIndex) noexcept;

	protected:
		std::vector<GameResourceRef<Texture2D>> textures;
		GameResourceRef<MaterialAsset> asset;
	};
}