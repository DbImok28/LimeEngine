// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "DxgiInfo.hpp"
#include "ExceptionsDX11.hpp"
#include "Platform/Windows/WindowsExceptions.hpp"

#ifdef PRAGMA_COMMENT_LIB
	#pragma comment(lib, "dxguid.lib")
#endif // PRAGMA_COMMENT_LIB

namespace LimeEngine
{
	DxgiInfo::DxgiInfo()
	{
		typedef HRESULT(WINAPI * DXGIGetDebugInterface)(REFIID, void**);
		const auto hModDxgiDebug = LoadLibraryEx(TEXT("dxgidebug.dll"), nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
		if (!hModDxgiDebug) throw HR_LAST_EXCEPTION();

		const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface")));
		if (!DxgiGetDebugInterface) throw HR_LAST_EXCEPTION();

		GFX_CHECK_HR_NOINFO(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &pDxgiInfoQueue));
	}

	void DxgiInfo::Set() noexcept
	{
		next = GetMessageCount();
	}

	std::vector<std::string> DxgiInfo::GetMessages() const
	{
		std::vector<std::string> messages;

		const uint64 count = GetMessageCount();
		messages.reserve(count - next);

		for (uint64 i = next; i < count; i++)
		{
			messages.emplace_back(GetMessageByIndex(i).second);
		}
		return messages;
	}

	std::vector<std::string> DxgiInfo::GetAllMessages()
	{
		const uint64 count = GetMessageCount();
		for (uint64 i = lastMessageByID; i < count; i++)
		{
			auto [id, message] = GetMessageByIndex(i);
			auto itemIter = messageByID.find(id);
			if (itemIter != std::end(messageByID))
			{
				++itemIter->second.first;
			}
			else
			{
				messageByID.emplace(id, std::make_pair<uint, std::string>(1u, std::move(message)));
			}
		}

		std::vector<std::string> messages;
		messages.reserve(messageByID.size());
		for (auto& item : messageByID)
		{
			auto [count, message] = item.second;
			messages.emplace_back(std::format("({}) {}", count, message));
		}
		return messages;
	}

	uint64 DxgiInfo::GetMessageCount() const
	{
		return pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	}

	std::string DxgiInfo::FormatInfoQueueMessage(const DXGI_INFO_QUEUE_MESSAGE& message) const
	{
		std::string severity;
		switch (message.Severity)
		{
			case DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION: severity = "Corruption"; break;
			case DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR: severity = "Error"; break;
			case DXGI_INFO_QUEUE_MESSAGE_SEVERITY_WARNING: severity = "Warning"; break;
			case DXGI_INFO_QUEUE_MESSAGE_SEVERITY_INFO: severity = "Info"; break;
			case DXGI_INFO_QUEUE_MESSAGE_SEVERITY_MESSAGE: severity = "Message"; break;
			default: severity = "Unknown"; break;
		}

		std::string category;
		switch (message.Category)
		{
			case DXGI_INFO_QUEUE_MESSAGE_CATEGORY_UNKNOWN: category = "Unknown"; break;
			case DXGI_INFO_QUEUE_MESSAGE_CATEGORY_MISCELLANEOUS: category = "Miscellaneous"; break;
			case DXGI_INFO_QUEUE_MESSAGE_CATEGORY_INITIALIZATION: category = "Initialization"; break;
			case DXGI_INFO_QUEUE_MESSAGE_CATEGORY_CLEANUP: category = "Cleanup"; break;
			case DXGI_INFO_QUEUE_MESSAGE_CATEGORY_COMPILATION: category = "Compilation"; break;
			case DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_CREATION: category = "State Creation"; break;
			case DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_SETTING: category = "State Setting"; break;
			case DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_GETTING: category = "State Getting"; break;
			case DXGI_INFO_QUEUE_MESSAGE_CATEGORY_RESOURCE_MANIPULATION: category = "Resource Manipulation"; break;
			case DXGI_INFO_QUEUE_MESSAGE_CATEGORY_EXECUTION: category = "Execution"; break;
			case DXGI_INFO_QUEUE_MESSAGE_CATEGORY_SHADER: category = "Shader"; break;
			default: category = "Unknown"; break;
		}

		return std::format("[DXGI Message {}][{}][{}] {}", message.ID, category, severity, message.pDescription);
	}

	std::pair<uint, std::string> DxgiInfo::GetMessageByIndex(uint64 index) const
	{
		size_t messageLength;

#pragma warning(suppress : 6001)
		GFX_CHECK_HR_NOINFO(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, index, nullptr, &messageLength));

		auto bytes = MakeUnique<byte[]>(messageLength);
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		GFX_CHECK_HR_NOINFO(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, index, pMessage, &messageLength));

		return std::make_pair<uint, std::string>(pMessage->ID, FormatInfoQueueMessage(*pMessage));
	}
}
