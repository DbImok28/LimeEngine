// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

namespace LimeEngine
{
	enum class RenderAPI
	{
		Auto,
#ifdef LE_ENABLE_RENDER_API_DX11
		DirectX11
#endif
	};
}
