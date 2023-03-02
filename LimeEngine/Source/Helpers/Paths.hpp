#pragma once

namespace LimeEngine
{
	class Paths
	{
	private:
		static FPath GetPathToExeFolder() noexcept;

	public:
		static const FPath ExeFolder;
		static const FPath ShaderFolder;
		static const FPath ContentFolder;
	};
}