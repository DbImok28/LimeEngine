// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Graphics/RenderAPI.hpp"
#include "DirectXDef.hpp"
#include "ExceptionsDX11.hpp"
#include "GraphicAdapter.hpp"
#include "RenderStatesDX11.hpp"

namespace LimeEngine
{
	class RenderAPIDX11 final : public RenderAPI
	{
	public:
		RenderAPIDX11();
		void Initialize();

		virtual void SetPrimitiveTopology(PrimitiveTopology topology) const noexcept override;
		virtual void EnableBlend(uint8 renderTargetSlot, bool enable) override;
		virtual void DrawIndexed(uint indicesCount) const override;
		virtual void BindPipline() override;

		virtual RenderAPIType GetRenderAPIType() const noexcept override;
		virtual std::string GetVideoAdapterName() const noexcept override;

	public:
		ID3D11Device* GetDevice() const noexcept;
		ID3D11DeviceContext* GetDeviceContext() const noexcept;

		IDXGIFactory* GetDXGIFactory() const noexcept;
		const GraphicAdapter& GetGraphicAdapter() const noexcept;

	private:
		GraphicAdapter graphicAdapter;

		com_ptr<IDXGIFactory> dxgiFactory = nullptr;
		com_ptr<ID3D11Device> device = nullptr;
		com_ptr<ID3D11DeviceContext> deviceContext = nullptr;

		DepthStencilStateDX11 depthStencilState;
		RasterizerStateDX11 rasterizerState;
		SamplerStateDX11 samplerState;
		BlendStateDX11 blendState;
	};
}
