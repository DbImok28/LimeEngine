// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RenderStatesDX11.hpp"
#include "RenderAPIDX11.hpp"

namespace LimeEngine
{
	////////////////////////////////// DepthStencilStateDX11

	DepthStencilStateDX11::DepthStencilStateDX11()
	{
		Initialize();
	}

	void DepthStencilStateDX11::Bind()
	{
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().SetDepthStencilState(depthStencilState.Get(), 0u);
	}

	void DepthStencilStateDX11::Initialize()
	{
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().CreateDepthStencilState(depthStencilState.GetAddressOf());
	}

	////////////////////////////////// RasterizerStateDX11

	RasterizerStateDX11::RasterizerStateDX11()
	{
		Initialize();
	}

	void RasterizerStateDX11::Initialize()
	{
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().CreateRasterizerState(rasterizerState.GetAddressOf());
	}

	void RasterizerStateDX11::Bind()
	{
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().SetRasterizerState(rasterizerState.Get());
	}

	////////////////////////////////// SamplerStateDX11

	SamplerStateDX11::SamplerStateDX11()
	{
		Initialize();
	}

	void SamplerStateDX11::Bind()
	{
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().SetSamplers(0u, 1u, samplerState.GetAddressOf());
	}

	void SamplerStateDX11::Initialize()
	{
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().CreateSamplerState(samplerState.GetAddressOf());
	}
}
