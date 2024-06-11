// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "Graphics/RenderAPI.hpp"
#include "RenderAPIDX11.hpp"

namespace LimeEngine
{
	RenderAPIDX11::RenderAPIDX11()
	{
		Initialize();
	}

	void RenderAPIDX11::Initialize()
	{
		GFX_CHECK_HR(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(dxgiFactory.GetAddressOf())));

		std::vector<GraphicAdapter> adapters = GraphicAdapter::GetGraphicAdapters(dxgiFactory.Get());
		if (adapters.size() < 1) throw GFX_EXCEPTION_MSG("No found DXGI Adapters.");
		graphicAdapter = adapters[0];

		UINT flags = 0u;
#ifndef NDEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		GFX_CHECK_HR(D3D11CreateDevice(
			graphicAdapter.adapter,      // Adapter
			D3D_DRIVER_TYPE_UNKNOWN,     // DriverType
			nullptr,                     // Software
			flags,                       // Flags
			nullptr,                     // FeatureLevels
			0u,                          // FeatureLevels
			D3D11_SDK_VERSION,           // SDKVersion
			device.GetAddressOf(),       // Device
			nullptr,                     // FeatureLevel
			deviceContext.GetAddressOf() // ImmediateContext
			));

		depthStencilState.Initialize(device.Get());
		rasterizerState.Initialize(device.Get());
		samplerState.Initialize(device.Get());
	}

	void RenderAPIDX11::SetPrimitiveTopology(PrimitiveTopology topology) const noexcept
	{
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void RenderAPIDX11::DrawIndexed(uint indicesCount) const
	{
		GFX_CHECK_INFO(deviceContext->DrawIndexed(indicesCount, 0u, 0u));
	}

	void RenderAPIDX11::BindPipline()
	{
		depthStencilState.Bind();
		rasterizerState.Bind();
		samplerState.Bind();
	}

	RenderAPIType RenderAPIDX11::GetRenderAPIType() const noexcept
	{
		return RenderAPIType::DirectX11;
	}

	std::string RenderAPIDX11::GetVideoAdapterName() const noexcept
	{
		return graphicAdapter.GetName();
	}

	ID3D11Device* RenderAPIDX11::GetDevice() const noexcept
	{
		return device.Get();
	}

	ID3D11DeviceContext* RenderAPIDX11::GetDeviceContext() const noexcept
	{
		return deviceContext.Get();
	}

	IDXGIFactory* RenderAPIDX11::GetDXGIFactory() const noexcept
	{
		return dxgiFactory.Get();
	}

	const GraphicAdapter& RenderAPIDX11::GetGraphicAdapter() const noexcept
	{
		return graphicAdapter;
	}
}
