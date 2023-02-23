#include "lepch.hpp"
#include "GraphicAdapter.hpp"

namespace LimeEngine
{
	std::vector<GraphicAdapter> GraphicAdapter::adapters;

	std::vector<GraphicAdapter> GraphicAdapter::GetGraphicAdapters()
	{
		if (!adapters.empty()) return adapters;
		com_ptr<IDXGIFactory> pFactory;
		HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
		GFX_CHECK_HR_NOINFO(hr);

		IDXGIAdapter* pAdapter;
		UINT index = 0;
		while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
		{
			adapters.push_back(GraphicAdapter(pAdapter));
			++index;
		}
		return adapters;
	}

	GraphicAdapter::GraphicAdapter(IDXGIAdapter* pAdapter) : pAdapter(pAdapter)
	{
		HRESULT hr = pAdapter->GetDesc(&desc);
		GFX_CHECK_HR_NOINFO(hr);
	}
}