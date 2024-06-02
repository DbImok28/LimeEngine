// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Texture2D.hpp"
#include "Base/GameResource.hpp"
#include "Shaders.hpp"
#include "MaterialParameters.hpp"

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
		MaterialAsset(
			const ResourcePath& resourcePath, URef<VertexShader>&& vertexShader, URef<PixelShader>&& pixelShader, MaterialParameters&& parameters, MaterialType type) noexcept :
			GameResource(resourcePath),
			type(type), vertexShader(std::move(vertexShader)), pixelShader(std::move(pixelShader)), parameters(std::move(parameters))
		{}

		SRef<Material> Instantiate();

	public:
		MaterialType type;

		MaterialParameters parameters;
		URef<VertexShader> vertexShader;
		URef<PixelShader> pixelShader;
	};

	class Material
	{
		LE_DELETE_COPY(Material)

	public:
		Material(const GameResourceRef<MaterialAsset>& asset) noexcept : asset(asset), parameters(asset->parameters) {}

		void ApplyMaterial() noexcept;

		void SetTextureParameter(const GameResourceRef<Texture2D>& texture, uint slotIndex) noexcept;
		GameResourceRef<Texture2D> GetTextureParameter(uint slotIndex) noexcept;

		template <typename T>
		void SetParameter(const std::string& name, T value)
		{
			parameters.SetParameter(name, value);
		}

		template <typename T>
		T GetParameter(const std::string& name)
		{
			return parameters.GetParameter<T>(name);
		}

		GameResourceRef<MaterialAsset> GetAsset()
		{
			return asset;
		}

	protected:
		std::vector<GameResourceRef<Texture2D>> textures;
		GameResourceRef<MaterialAsset> asset;
		MaterialParameterValues parameters;
	};
}