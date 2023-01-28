#include "lepch.hpp"
#include "DxgiInfo.hpp"
#include "EngineExceptions.hpp"
#include "Helpers/StringHelper.hpp"

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

		CHECK_HR(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &pDxgiInfoQueue));
	}

	void DxgiInfo::Set() noexcept
	{
		next = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	}

	std::vector<std::string> DxgiInfo::GetMessages() const
	{
		std::vector<std::string> messages;
		const auto end = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
		for (auto i = next; i < end; i++)
		{
			std::string msg;
			SIZE_T messageLength;

#pragma warning(suppress : 6001)
			CHECK_HR(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength));

			auto bytes = std::make_unique<byte[]>(messageLength);
			auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
			CHECK_HR(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength));

			msg = pMessage->pDescription;
			messages.emplace_back(msg);
		}
		return messages;
	}
}