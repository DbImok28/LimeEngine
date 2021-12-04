#pragma once
#include "DirectXDef.hpp"
#include <vector>

class GraphicAdapter
{
public:
	static std::vector<GraphicAdapter> GetGraphicAdapters();
private:
	static std::vector<GraphicAdapter> adapters;
public:
	GraphicAdapter(IDXGIAdapter* pAdapter);
	IDXGIAdapter* pAdapter = nullptr;
	DXGI_ADAPTER_DESC desc;
};