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
		std::vector<std::string> GetAllMessages();

	private:
		uint64 GetMessageCount() const;
		std::string FormatInfoQueueMessage(const DXGI_INFO_QUEUE_MESSAGE& message) const;
		std::pair<uint, std::string> GetMessageByIndex(uint64 index) const;

	private:
		uint64 next = 0ull;
		com_ptr<IDXGIInfoQueue> pDxgiInfoQueue;

		uint64 lastMessageByID = 0ull;
		std::map<uint, std::pair<uint, std::string>> messageByID;
	};
}
