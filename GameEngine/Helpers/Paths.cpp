#include "Paths.hpp"
#include "../Window/WinApi.hpp"

std::wstring Paths::GetPathToExeFolder() noexcept
{
	WCHAR filePath[MAX_PATH];
	GetModuleFileNameW(NULL, filePath, MAX_PATH);

	int i;
	for (i = lstrlen(filePath) - 1; i >= 0; i--)
	{
		if (filePath[i] == L'\\' || filePath[i] == L'/')
		{
			filePath[i + 1] = L'\0';
			break;
		}
	}
	return std::wstring(filePath);
}

std::string Paths::GetDirectoryFromPath(const std::string& filePath)
{
	size_t pos = filePath.find_last_of("\\/");
	if (std::string::npos == pos)
		return "";
	return filePath.substr(0, pos + 1);
}

std::wstring Paths::GetDirectoryFromPath(const std::wstring& filePath)
{
	size_t pos = filePath.find_last_of(L"\\/");
	if (std::string::npos == pos)
		return L"";
	return filePath.substr(0, pos + 1);
}

std::string Paths::GetFileExtension(const std::string& filePath)
{
	size_t off = filePath.find_last_of('.');
	if (off == std::string::npos)
	{
		return "";
	}
	return std::string(filePath.substr(off + 1));
}

std::wstring Paths::GetFileExtension(const std::wstring& filePath)
{
	size_t off = filePath.find_last_of('.');
	if (off == std::wstring::npos)
	{
		return L"";
	}
	return std::wstring(filePath.substr(off + 1));
}

const std::wstring Paths::ExeFolder = GetPathToExeFolder();
const std::wstring Paths::ShaderFolder = ExeFolder;