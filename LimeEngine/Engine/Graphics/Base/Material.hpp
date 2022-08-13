#pragma once
#include <vector>
#include "Texture2D.hpp"
#include "../Systems/DX11/Shaders.hpp"
#include "../Systems/DX11/Buffers.hpp"

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
		Material(VertexShader* vertexShader, PixelShader* pixelShader, MaterialType type, size_t id) noexcept;
		void SetTextures(const std::vector<Texture2D*>& textures) noexcept;
		void AddTexture(Texture2D* texture) noexcept;
		const std::vector<Texture2D*>& GetTextures() const noexcept;
		template <typename T>
		void ApplyConstantBuffer(const RenderingSystemDX11& renderer, ConstantBuffer<T>& constantBuffer);
		void ApplyMaterial(const RenderingSystemDX11& renderer) noexcept;

	public:
		size_t id;

	private:
		std::vector<Texture2D*> textures;
		VertexShader* vertexShader;
		PixelShader* pixelShader;
		MaterialType type;
	};

	template <typename T>
	void Material::ApplyConstantBuffer(const RenderingSystemDX11& renderer, ConstantBuffer<T>& constantBuffer)
	{
		constantBuffer.ApplyChanges();
		constantBuffer.Bind();
	}
}