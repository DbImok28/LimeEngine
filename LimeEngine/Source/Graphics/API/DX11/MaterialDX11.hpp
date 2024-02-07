// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/Material.hpp"
#include "ShadersDX11.hpp"

namespace LimeEngine
{
	class MaterialDX11 : public MaterialBase
	{
		LE_DELETE_COPY(MaterialDX11)

	public:
		MaterialDX11(
			const ResourcePath& resourcePath, std::unique_ptr<VertexShaderDX11>&& vertexShader, std::unique_ptr<PixelShaderDX11>&& pixelShader, MaterialType type) noexcept;
		virtual void ApplyMaterial() noexcept override;

	private:
		std::unique_ptr<VertexShaderDX11> vertexShader;
		std::unique_ptr<PixelShaderDX11> pixelShader;
	};
}