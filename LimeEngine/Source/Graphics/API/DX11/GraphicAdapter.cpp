// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "GraphicAdapter.hpp"

namespace LimeEngine
{
	std::vector<GraphicAdapter> GraphicAdapter::adapters;

	std::vector<GraphicAdapter> GraphicAdapter::GetGraphicAdapters(IDXGIFactory* dxgiFactory)
	{
		if (!adapters.empty()) return adapters;
		IDXGIAdapter* adapter;
		UINT index = 0;
		while (SUCCEEDED(dxgiFactory->EnumAdapters(index, &adapter)))
		{
			adapters.push_back(GraphicAdapter(adapter));
			++index;
		}
		return adapters;
	}

	GraphicAdapter::GraphicAdapter(IDXGIAdapter* adapter) : adapter(adapter)
	{
		HRESULT hr = adapter->GetDesc(&desc);
		GFX_CHECK_HR_NOINFO(hr);
	}

	std::string GraphicAdapter::GetName() const noexcept
	{
		return StringUtility::WideToChar8(desc.Description);
	}
}