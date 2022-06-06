#include "MaterialDX11.hpp"
#include "../../Base/Material.hpp"

namespace LimeEngine
{
	MaterialDX11::MaterialDX11(ID3D11DeviceContext* deviceContext, Material* material, VertexShader* vertexShader, PixelShader* pixelShader) noexcept :
		material(material), deviceContext(deviceContext), vertexShader(vertexShader), pixelShader(pixelShader) {}

	void MaterialDX11::ApplyMaterial() const noexcept
	{
		deviceContext->IASetInputLayout(vertexShader->GatInputLoyout());
		deviceContext->VSSetShader(vertexShader->GetShader(), NULL, 0);
		deviceContext->PSSetShader(pixelShader->GetShader(), NULL, 0);
		for (auto& texture : material->GetTextures())
		{
			deviceContext->PSSetShaderResources(0, 1, texture->renderTexture.GetViewAddress());
		}
	}
}