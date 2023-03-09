#pragma once
#include "DirectXDef.hpp"
#include "ExceptionsDX11.hpp"

namespace LimeEngine
{
	class GraphicAdapter
	{
	public:
		static std::vector<GraphicAdapter> GetGraphicAdapters(IDXGIFactory* dxgiFactory);

	private:
		static std::vector<GraphicAdapter> adapters;

	public:
		GraphicAdapter() noexcept = default;
		explicit GraphicAdapter(IDXGIAdapter* adapter);
		IDXGIAdapter* adapter = nullptr;
		DXGI_ADAPTER_DESC desc = { 0 };
	};
}