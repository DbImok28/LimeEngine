#pragma once
#include "Texture2D.hpp"
#include "../Systems/DX11/MaterialDX11.hpp"
#include <vector>

namespace LimeEngine
{
	class Material
	{
	public:
		Material(ID3D11DeviceContext* deviceContext, VertexShader* vertexShader, PixelShader* pixelShader, size_t Id) noexcept;
		void SetTextures(std::vector<Texture2D*> textures) noexcept;
		void AddTexture(Texture2D* texture) noexcept;
		const std::vector<Texture2D*>& GetTextures() const noexcept;

		MaterialDX11 renderMaterial;
		size_t Id;
	private:
		std::vector<Texture2D*> textures;
	};
}