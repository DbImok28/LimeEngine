// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Graphics/VertexArray.hpp"
#include "BuffersDX11.hpp"

namespace LimeEngine
{
	class VertexArrayDX11 : public VertexArray
	{
	public:
		virtual void Bind() override;

		virtual void AddVertexBuffer(const SRef<VertexBuffer>& vertexBuffer) noexcept override;

	private:
		std::vector<ID3D11Buffer*> dx11Buffers;
		std::vector<uint> strides;
		std::vector<uint> offsets;
	};
}
