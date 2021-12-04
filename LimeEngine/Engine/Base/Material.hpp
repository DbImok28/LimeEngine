#pragma once
#include "Texture2D.hpp"
#include "../Graphics/Shaders.hpp"
#include "../Graphics/Buffers/ConstantBuffer.hpp"

class Material
{
public:
	Material(ID3D11DeviceContext* deviceContext, VertexShader* vertexShader, PixelShader* pixelShader) noexcept;
	void SetTextures(std::vector<Texture2D*> textures);
	void AddTexture(Texture2D* texture);
	template<typename T>
	void ApplyConstantBuffer(ConstantBuffer<T>& constantBuffer) noexcept;
	void Apply() const noexcept;
private:
	std::vector<Texture2D*> textures; // TODO: Array and view
	ID3D11DeviceContext* deviceContext;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
};

template<typename T>
void Material::ApplyConstantBuffer(ConstantBuffer<T>& constantBuffer) noexcept
{
	constantBuffer.ApplyChanges();
	deviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
}