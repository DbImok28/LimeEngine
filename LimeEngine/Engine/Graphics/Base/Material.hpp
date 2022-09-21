#pragma once
#include <vector>
#include "Texture2D.hpp"
#include "IBindable.hpp"

namespace LimeEngine
{
	enum class MaterialType
	{
		Unknown,
		Solid
	};

	class Material : public GameResource
	{
	public:
		Material(std::string path, MaterialType type) noexcept;

		virtual void ApplyMaterial() noexcept = 0;
		void AddTexture(GameResourceRef<Texture2D> texture) noexcept;
		const std::vector<GameResourceRef<Texture2D>>& GetTextures() const noexcept;
		void SetTextures(const std::vector<GameResourceRef<Texture2D>>& textures) noexcept;
		MaterialType GetType() const noexcept;

	protected:
		std::vector<GameResourceRef<Texture2D>> textures;
		MaterialType type;
	};

	class MasterMaterial : public Material
	{
	public:
		MasterMaterial(std::string path, IBindable* vertexShader, IBindable* pixelShader, MaterialType type) noexcept;
		virtual void ApplyMaterial() noexcept override;

	private:
		IBindable* vertexShader;
		IBindable* pixelShader;
	};
}