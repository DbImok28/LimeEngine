#include "lepch.hpp"
#include "Paths.hpp"

#if defined(LE_BUILD_PLATFORM_WINDOWS)
	#include "Platform/Windows/WinApi.hpp"
	#include "Platform/Windows/WindowsExceptions.hpp"
#endif

namespace LimeEngine
{
	std::wstring Paths::GetPathToExeFolder() noexcept
	{
#if defined(LE_BUILD_PLATFORM_WINDOWS)
		std::array<wchar_t, MAX_PATH> filePath = { '\0' };
		if (GetModuleFileNameW(NULL, filePath.data(), MAX_PATH) == 0)
		{
			throw HR_LAST_EXCEPTION();
		}
#endif
		return std::filesystem::path(filePath.data()).remove_filename().wstring();
	}

	const std::wstring Paths::ExeFolder = GetPathToExeFolder();
	const std::wstring Paths::ShaderFolder = ExeFolder;
}