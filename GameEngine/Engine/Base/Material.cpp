#include "Material.hpp"

Material::Material()
{
}

Material::Material(ID3D11DeviceContext* deviceContext, VertexShader* vertexShader, PixelShader* pixelShader)
	: deviceContext(deviceContext), vertexShader(vertexShader), pixelShader(pixelShader)
{
}

void Material::Set(ID3D11DeviceContext* deviceContext, VertexShader* vertexShader, PixelShader* pixelShader)
{
	this->deviceContext = deviceContext;
	this->vertexShader = vertexShader;
	this->pixelShader = pixelShader;
}

void Material::SetTextures(std::vector<Texture2D> textures)
{
	this->textures = textures;
}

void Material::Apply()
{
	deviceContext->IASetInputLayout(vertexShader->GatInputLoyout());
	deviceContext->VSSetShader(vertexShader->GetShader(), NULL, 0);
	deviceContext->PSSetShader(pixelShader->GetShader(), NULL, 0);
	for (auto& texture : textures)
	{
		deviceContext->PSSetShaderResources(0, 1, texture.GetViewAddress());
	}
}