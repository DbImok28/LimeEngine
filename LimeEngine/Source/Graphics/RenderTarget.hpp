// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Texture2D.hpp"

namespace LimeEngine
{
	class DepthStencil
	{
		LE_DELETE_COPY(DepthStencil);

	public:
		URef<DepthStencil> Create(uint width, uint height);

		DepthStencil() = default;

	public:
		virtual void Clear(float clearDepth = 1.0f, uint8 clearStencil = 0u) = 0;
		virtual void ClearDepth(float clearDepth = 1.0f) = 0;
		virtual void ClearStencil(uint clearStencil = 0u) = 0;
		virtual void Resize(uint width, uint height) = 0;
		virtual void Reset() = 0;
		virtual URef<Texture2D> GetTexture() = 0;
	};

	class RenderTarget
	{
		LE_DELETE_COPY(RenderTarget);

	public:
		URef<RenderTarget> Create(uint width, uint height);

		RenderTarget() = default;

	public:
		virtual void Bind(DepthStencil* depthStencil = nullptr) = 0;
		virtual void Clear(const float* clearColor) = 0;
		virtual bool Resize(uint width, uint height) = 0;
		virtual void Reset() = 0;
		virtual URef<Texture2D> GetTexture() = 0;
	};
}
