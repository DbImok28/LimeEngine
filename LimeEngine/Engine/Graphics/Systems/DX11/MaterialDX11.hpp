#pragma once
#include "DirectXDef.hpp"
#include "Shaders.hpp"
#include "ConstantBuffer.hpp"
#include "RenderingSystemDX11.hpp"

namespace LimeEngine
{
	class Material;

	class MaterialDX11
	{
	public:
		MaterialDX11(const RenderingSystemDX11& renderer, Material* material, VertexShader* vertexShader, PixelShader* pixelShader) noexcept;
		template<typename T>
		void ApplyConstantBuffer(ConstantBuffer<T>& constantBuffer);
		void ApplyMaterial() const noexcept;

	private:
		// TODO: Array and texture view
		Material* material;

		const RenderingSystemDX11& renderer;
		VertexShader* vertexShader;
		PixelShader* pixelShader;
	};

	template<typename T>
	void MaterialDX11::ApplyConstantBuffer(ConstantBuffer<T>& constantBuffer)
	{
		constantBuffer.ApplyChanges();
		renderer.deviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
	}
}