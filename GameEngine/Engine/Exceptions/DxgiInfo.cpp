#include "DxgiInfo.hpp"
#include "EngineExceptions.hpp"
#include <memory>
#include "../Helpers/StringHelper.hpp"

#pragma comment(lib, "dxguid.lib")

DxgiInfo::DxgiInfo()
{
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);
	const auto hModDxgiDebug = LoadLibraryEx(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	if (hModDxgiDebug == nullptr)
		throw HR_LAST_EXCEPTION();
	
	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"))
		);
	if (DxgiGetDebugInterface == nullptr)
		throw HR_LAST_EXCEPTION();
	
	HRESULT hr = DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &pDxgiInfoQueue);
	ERROR_IF(hr);
}

void DxgiInfo::Set() noexcept
{
	next = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::wstring> DxgiInfo::GetMessages() const
{
	std::vector<std::wstring> messages;
	const auto end = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	std::string msg;
	for (auto i = next; i < end; i++)
	{
		SIZE_T messageLength;

		#pragma warning(suppress: 6001)
		HRESULT hr = pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength);
		ERROR_IF(hr);

		auto bytes = std::make_unique<byte[]>(messageLength);
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		hr = pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength);
		ERROR_IF(hr);

		msg = pMessage->pDescription;
		messages.emplace_back(StringHelper::StringToWide(msg));
	}
	return messages;
}