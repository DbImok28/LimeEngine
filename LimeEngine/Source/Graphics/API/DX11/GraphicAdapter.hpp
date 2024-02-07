// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "DirectXDef.hpp"
#include "ExceptionsDX11.hpp"
#include "Utility/StringUtility.hpp"

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

		std::string GetName() const noexcept;

	public:
		IDXGIAdapter* adapter = nullptr;
		DXGI_ADAPTER_DESC desc = { 0 };
	};
}