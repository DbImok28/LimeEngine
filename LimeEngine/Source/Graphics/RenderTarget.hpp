// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

namespace LimeEngine
{
	class DepthStencil
	{
	public:
		std::unique_ptr<DepthStencil> Create(uint width, uint height);

	public:
		virtual void Clear(float clearDepth = 1.0f, uint clearStencil = 0u) = 0;
		virtual void ClearDepth(float clearDepth = 1.0f) = 0;
		virtual void ClearStencil(uint clearStencil = 0u) = 0;
		virtual void Resize(uint width, uint height) = 0;
		virtual void Reset() = 0;
	};

	class RenderTarget
	{
	public:
		std::unique_ptr<RenderTarget> Create(uint width, uint height);

	public:
		virtual void Bind(DepthStencil* depthStencil = nullptr) = 0;
		virtual void Clear(const float* clearColor) = 0;
		virtual bool Resize(uint width, uint height) = 0;
		virtual void Reset() = 0;
	};
}
