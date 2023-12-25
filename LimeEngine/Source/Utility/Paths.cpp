// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Paths.hpp"
#include "Platform/Platform.hpp"

namespace LimeEngine
{
	FPath Paths::GetPathToExeFolder()
	{
		return Platform::GetPathToExeFolder();
	}

	const FPath Paths::ExeFolder = GetPathToExeFolder();
	const FPath Paths::ShaderFolder = "Shaders";
	const FPath Paths::ContentFolder = "Content";
}