// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/IBindable.hpp"
#include "DirectXDef.hpp"

namespace LimeEngine
{
	class DepthStencilStateDX11 final : public IBindable
	{
	public:
		DepthStencilStateDX11() = default;

		void Initialize(ID3D11Device* device = nullptr);
		virtual void Bind() override;

	private:
		com_ptr<ID3D11DepthStencilState> depthStencilState = nullptr;
	};

	class RasterizerStateDX11 final : public IBindable
	{
	public:
		RasterizerStateDX11() = default;

		void Initialize(ID3D11Device* device = nullptr);
		virtual void Bind() override;

	private:
		com_ptr<ID3D11RasterizerState> rasterizerState = nullptr;
	};

	class SamplerStateDX11 final : public IBindable
	{
	public:
		SamplerStateDX11() = default;

		void Initialize(ID3D11Device* device = nullptr);
		virtual void Bind() override;

	private:
		com_ptr<ID3D11SamplerState> samplerState = nullptr;
	};

	class BlendStateDX11 final : public IBindable
	{
	public:
		BlendStateDX11() = default;

		void Initialize(ID3D11Device* device = nullptr);
		virtual void Bind() override;
		void EnableBlend(uint8 renderTargetSlot, bool enable);

	private:
		com_ptr<ID3D11BlendState> blendState = nullptr;
	};
}
