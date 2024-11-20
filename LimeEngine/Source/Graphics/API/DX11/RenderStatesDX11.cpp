// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RenderStatesDX11.hpp"
#include "RenderAPIDX11.hpp"

namespace LimeEngine
{
	////////////////////////////////// DepthStencilStateDX11

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

	////////////////////////////////// BlendStateDX11

	void BlendStateDX11::Initialize(ID3D11Device* device)
	{
		if (!device) device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();

		D3D11_BLEND_DESC blendDesc = {};
		blendDesc.AlphaToCoverageEnable = FALSE;
		blendDesc.IndependentBlendEnable = TRUE;
		const D3D11_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc = {
			FALSE,
			D3D11_BLEND::D3D11_BLEND_SRC_ALPHA,
			D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD,
			D3D11_BLEND::D3D11_BLEND_ONE,
			D3D11_BLEND::D3D11_BLEND_ZERO,
			D3D11_BLEND_OP::D3D11_BLEND_OP_ADD,
			D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL,
		};
		for (auto& renderTargetBlendDesc : blendDesc.RenderTarget)
		{
			renderTargetBlendDesc = defaultRenderTargetBlendDesc;
		}

		GFX_CHECK_HR(device->CreateBlendState(&blendDesc, blendState.GetAddressOf()));

		D3D11_BLEND_DESC blendDesc2;
		blendState->GetDesc(&blendDesc2);
	}

	void BlendStateDX11::Bind()
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->OMSetBlendState(blendState.Get(), nullptr, 0xffffffff);
	}

	void BlendStateDX11::EnableBlend(uint8 renderTargetSlot, bool enable)
	{
		if (renderTargetSlot > D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)
		{
			LE_ASSERT(false, "Invalid render target slot to enable blending");
			return;
		}

		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();

		D3D11_BLEND_DESC blendDesc;
		blendState->GetDesc(&blendDesc);

		if (blendDesc.RenderTarget[renderTargetSlot].BlendEnable != enable)
		{
			const D3D11_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {
				TRUE,
				D3D11_BLEND::D3D11_BLEND_SRC_ALPHA,
				D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA,
				D3D11_BLEND_OP::D3D11_BLEND_OP_ADD,
				D3D11_BLEND::D3D11_BLEND_ONE,
				D3D11_BLEND::D3D11_BLEND_ZERO,
				D3D11_BLEND_OP::D3D11_BLEND_OP_ADD,
				D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL,
			};
			blendDesc.RenderTarget[renderTargetSlot] = renderTargetBlendDesc;
			GFX_CHECK_HR(device->CreateBlendState(&blendDesc, &blendState));
		}
	}
}
