#include "MaterialDX11.hpp"
#include "../../Base/Material.hpp"

namespace LimeEngine
{
	MaterialDX11::MaterialDX11(const RenderingSystemDX11& renderer, Material* material, VertexShader* vertexShader, PixelShader* pixelShader) noexcept :
		material(material), renderer(renderer), vertexShader(vertexShader), pixelShader(pixelShader)
	{}

	void MaterialDX11::ApplyMaterial() const noexcept
	{
		auto deviceContext = renderer.deviceContext.Get();

		deviceContext->IASetInputLayout(vertexShader->GatInputLoyout());
		deviceContext->VSSetShader(vertexShader->GetShader(), NULL, 0);
		deviceContext->PSSetShader(pixelShader->GetShader(), NULL, 0);
		for (auto& texture : material->GetTextures())
		{
			deviceContext->PSSetShaderResources(0, 1, texture->renderTexture.GetViewAddress());
		}
	}
}