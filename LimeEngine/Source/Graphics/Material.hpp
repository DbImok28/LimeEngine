// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Texture2D.hpp"
#include "IBindable.hpp"

namespace LimeEngine
{
	enum class MaterialType
	{
		Unknown,
		Solid
	};

	class MaterialInstance;

	class Material : public GameResource
	{
		LE_DELETE_COPY(Material)

	public:
		Material(const ResourcePath& resourcePath, MaterialType type) noexcept;

		virtual void ApplyMaterial() noexcept = 0;
		MaterialType GetType() const noexcept;

		std::shared_ptr<MaterialInstance> GetInstance();

	protected:
		MaterialType type;
	};

	class MasterMaterial : public Material
	{
		LE_DELETE_COPY(MasterMaterial)

	public:
		MasterMaterial(const ResourcePath& resourcePath, std::unique_ptr<IBindable> vertexShader, std::unique_ptr<IBindable> pixelShader, MaterialType type) noexcept;
		virtual void ApplyMaterial() noexcept override;

	private:
		std::unique_ptr<IBindable> vertexShader;
		std::unique_ptr<IBindable> pixelShader;
	};

	class MaterialInstance
	{
	public:
		explicit MaterialInstance(GameResourceRef<Material> material) : material(material) {}
		virtual ~MaterialInstance() = default;

		void AddTexture(GameResourceRef<Texture2D> texture) noexcept;
		const std::vector<GameResourceRef<Texture2D>>& GetTextures() const noexcept;
		void SetTextures(const std::vector<GameResourceRef<Texture2D>>& textures) noexcept;

		virtual void ApplyMaterial() noexcept;

	private:
		GameResourceRef<Material> material;
		std::vector<GameResourceRef<Texture2D>> textures;
	};
}