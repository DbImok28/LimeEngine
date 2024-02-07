// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "MaterialDX11.hpp"

namespace LimeEngine
{
	MaterialDX11::MaterialDX11(
		const ResourcePath& resourcePath, std::unique_ptr<VertexShaderDX11>&& vertexShader, std::unique_ptr<PixelShaderDX11>&& pixelShader, MaterialType type) noexcept :
		MaterialBase(resourcePath, type),
		vertexShader(std::move(vertexShader)), pixelShader(std::move(pixelShader))
	{}

	void MaterialDX11::ApplyMaterial() noexcept
	{
		vertexShader->Bind();
		pixelShader->Bind();
	}
}
