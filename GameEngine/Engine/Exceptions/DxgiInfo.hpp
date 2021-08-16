#pragma once
#include <vector>
#include <string>
#include <wrl.h>
#include <dxgidebug.h>

class DxgiInfo
{
public:
	DxgiInfo();
	DxgiInfo(const DxgiInfo&) = delete;
	DxgiInfo& operator=(const DxgiInfo&) = delete;
	void Set() noexcept;
	std::vector<std::wstring> GetMessages() const;
private:
	unsigned long long next = 0ull;
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> pDxgiInfoQueue;
};