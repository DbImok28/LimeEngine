#pragma once
#include <vector>
#include "Texture2D.hpp"
#include "../Systems/DX11/MaterialDX11.hpp"

namespace LimeEngine
{
	class Material
	{
	public:
		Material(const RenderingSystemDX11& renderer, VertexShader* vertexShader, PixelShader* pixelShader, size_t Id) noexcept;
		void SetTextures(const std::vector<Texture2D*>& textures) noexcept;
		void AddTexture(Texture2D* texture) noexcept;
		const std::vector<Texture2D*>& GetTextures() const noexcept;

		MaterialDX11 renderMaterial;
		size_t Id;

	private:
		std::vector<Texture2D*> textures;
	};
}