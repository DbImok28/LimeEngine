#pragma once
#include "CoreBase.hpp"

namespace LimeEngine
{
	enum class RenderAPI
	{
		Auto,
#ifdef ENABLE_RENDER_API_DX11
		DirectX11
#endif
	};
}
