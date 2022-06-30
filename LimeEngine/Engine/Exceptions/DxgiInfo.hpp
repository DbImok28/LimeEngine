#pragma once
#include "../Graphics/Systems/DX11/DirectXDef.hpp"
#include <vector>
#include <string>
#include <dxgidebug.h>

namespace LimeEngine
{
	class DxgiInfo
	{
	public:
		DxgiInfo();
		DxgiInfo(const DxgiInfo&) = delete;
		DxgiInfo& operator=(const DxgiInfo&) = delete;
		void Set() noexcept;
		std::vector<std::string> GetMessages() const;

	private:
		unsigned long long next = 0ull;
		com_ptr<IDXGIInfoQueue> pDxgiInfoQueue;
	};
}