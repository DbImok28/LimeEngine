#pragma once
#include "Shaders.hpp"
#include "ConstantBuffer.hpp"

namespace LimeEngine
{
	class Material;

	class MaterialDX11
	{
	public:
		MaterialDX11(ID3D11DeviceContext* deviceContext, Material* material, VertexShader* vertexShader, PixelShader* pixelShader) noexcept;
		template<typename T>
		void ApplyConstantBuffer(ConstantBuffer<T>& constantBuffer);
		void ApplyMaterial() const noexcept;

	private:
		// TODO: Array and texture view
		Material* material;

		ID3D11DeviceContext* deviceContext;
		VertexShader* vertexShader;
		PixelShader* pixelShader;
	};

	template<typename T>
	void MaterialDX11::ApplyConstantBuffer(ConstantBuffer<T>& constantBuffer)
	{
		constantBuffer.ApplyChanges();
		deviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
	}
}