#pragma once
#include "DirectXDef.hpp"

namespace LimeEngine
{
	class GraphicAdapter
	{
	public:
		static std::vector<GraphicAdapter> GetGraphicAdapters();

	private:
		static std::vector<GraphicAdapter> adapters;

	public:
		explicit GraphicAdapter(IDXGIAdapter* pAdapter);
		IDXGIAdapter* pAdapter = nullptr;
		DXGI_ADAPTER_DESC desc;
	};
}