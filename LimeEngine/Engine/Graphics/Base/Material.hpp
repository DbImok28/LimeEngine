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

	class Material
	{
	public:
		Material(MaterialType type, size_t id) noexcept;
		virtual ~Material() = default;

		virtual void ApplyMaterial() noexcept = 0;
		void AddTexture(Texture2D* texture) noexcept;
		const std::vector<Texture2D*>& GetTextures() const noexcept;
		void SetTextures(const std::vector<Texture2D*>& textures) noexcept;
		MaterialType GetType() const noexcept;
		size_t GetID() const noexcept;

	protected:
		std::vector<Texture2D*> textures;
		MaterialType type;

	private:
		size_t id;
	};

	class MasterMaterial : public Material
	{
	public:
		MasterMaterial(IBindable* vertexShader, IBindable* pixelShader, MaterialType type, size_t id) noexcept;
		virtual void ApplyMaterial() noexcept override;

	private:
		IBindable* vertexShader;
		IBindable* pixelShader;
	};
}