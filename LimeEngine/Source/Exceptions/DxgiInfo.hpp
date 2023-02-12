#pragma once
#include "Graphics/Systems/DX11/DirectXDef.hpp"
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