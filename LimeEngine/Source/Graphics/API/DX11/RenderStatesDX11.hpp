// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/IBindable.hpp"
#include "RenderContextDX11.hpp"

namespace LimeEngine
{
	class DepthStencilStateDX11 final : public IBindable
	{
	public:
		DepthStencilStateDX11();

		virtual void Bind() override;

	private:
		void Initialize();

	private:
		com_ptr<ID3D11DepthStencilState> depthStencilState = nullptr;
	};

	class RasterizerStateDX11 final : public IBindable
	{
	public:
		RasterizerStateDX11();

	private:
		void Initialize();

	public:
		virtual void Bind() override;

	private:
		com_ptr<ID3D11RasterizerState> rasterizerState = nullptr;
	};

	class SamplerStateDX11 final : public IBindable
	{
	public:
		SamplerStateDX11();
		virtual void Bind() override;

	private:
		void Initialize();

	private:
		com_ptr<ID3D11SamplerState> samplerState = nullptr;
	};
}
