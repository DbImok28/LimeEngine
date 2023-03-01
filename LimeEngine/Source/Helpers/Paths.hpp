#pragma once

namespace LimeEngine
{
	class Paths
	{
	private:
		static std::wstring GetPathToExeFolder() noexcept;

	public:
		static const std::wstring ExeFolder;
		static const std::wstring ShaderFolder;
	};
}