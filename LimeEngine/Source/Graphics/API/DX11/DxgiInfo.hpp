// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/API/DX11/DirectXDef.hpp"
#include <dxgidebug.h>

namespace LimeEngine
{
	class DxgiInfo
	{
		LE_DELETE_COPY(DxgiInfo);

	public:
		DxgiInfo();
		void Set() noexcept;
		std::vector<std::string> GetMessages() const;

	private:
		unsigned long long next = 0ull;
		com_ptr<IDXGIInfoQueue> pDxgiInfoQueue;
	};
}