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
		//Initialize();
	}

	void DepthStencilStateDX11::Initialize(ID3D11Device* device)
	{
		if (!device) device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();

		D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
		depthStencilStateDesc.DepthEnable = TRUE;
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
		depthStencilStateDesc.StencilEnable = FALSE;
		depthStencilStateDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		depthStencilStateDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

		D3D11_DEPTH_STENCILOP_DESC defaultStencilOp = { D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS };
		depthStencilStateDesc.FrontFace = defaultStencilOp;
		depthStencilStateDesc.BackFace = defaultStencilOp;

		GFX_CHECK_HR(device->CreateDepthStencilState(&depthStencilStateDesc, depthStencilState.GetAddressOf()));
	}

	void DepthStencilStateDX11::Bind()
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->OMSetDepthStencilState(depthStencilState.Get(), 0u);
	}

	////////////////////////////////// RasterizerStateDX11

	RasterizerStateDX11::RasterizerStateDX11()
	{
		//Initialize();
	}

	void RasterizerStateDX11::Initialize(ID3D11Device* device)
	{
		if (!device) device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();

		// TODO:Add fill mode and cull mode switch
		D3D11_RASTERIZER_DESC rasterizerDesc;
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		rasterizerDesc.FrontCounterClockwise = FALSE;
		rasterizerDesc.DepthBias = D3D11_DEFAULT_DEPTH_BIAS;
		rasterizerDesc.DepthBiasClamp = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
		rasterizerDesc.SlopeScaledDepthBias = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		rasterizerDesc.DepthClipEnable = TRUE;
		rasterizerDesc.ScissorEnable = FALSE;
		rasterizerDesc.MultisampleEnable = FALSE;
		rasterizerDesc.AntialiasedLineEnable = FALSE;

		GFX_CHECK_HR(device->CreateRasterizerState(&rasterizerDesc, rasterizerState.GetAddressOf()));
	}

	void RasterizerStateDX11::Bind()
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->RSSetState(rasterizerState.Get());
	}

	////////////////////////////////// SamplerStateDX11

	SamplerStateDX11::SamplerStateDX11()
	{
		//Initialize();
	}

	void SamplerStateDX11::Initialize(ID3D11Device* device)
	{
		if (!device) device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();

		D3D11_SAMPLER_DESC sampDesc;
		sampDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.MipLODBias = 0.0f;
		sampDesc.MaxAnisotropy = 1u;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = -D3D11_FLOAT32_MAX;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		GFX_CHECK_HR(device->CreateSamplerState(&sampDesc, samplerState.GetAddressOf()));
	}

	void SamplerStateDX11::Bind()
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->PSSetSamplers(0u, 1u, samplerState.GetAddressOf());
	}
}
