// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "IBindable.hpp"
#include "Graphics/Material.hpp"

namespace LimeEngine
{
	class VertexShader : public IBindable
	{
	public:
		static std::unique_ptr<VertexShader> Create(const FPath& filePath, MaterialType materialType);
	};

	class PixelShader : public IBindable
	{
	public:
		static std::unique_ptr<PixelShader> Create(const FPath& filePath);
	};
}
