#pragma once

namespace LimeEngine
{
	class Paths
	{
	private:
		static std::wstring GetPathToExeFolder() noexcept;

	public:
		static std::string GetDirectoryFromPath(const std::string& filePath);
		static std::wstring GetDirectoryFromPath(const std::wstring& filePath);
		static std::string GetFileExtension(const std::string& filePath);
		static std::wstring GetFileExtension(const std::wstring& filePath);
		static const std::wstring ExeFolder;
		static const std::wstring ShaderFolder;
	};
}