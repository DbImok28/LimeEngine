// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
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