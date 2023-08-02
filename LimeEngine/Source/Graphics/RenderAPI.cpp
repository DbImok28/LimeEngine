#include "RenderAPI.hpp"

std::string LimeEngine::RenderAPIToString(RenderAPI api) noexcept
{
	switch (api)
	{
		case RenderAPI::Auto:
#ifdef LE_ENABLE_RENDER_API_DX11
		case RenderAPI::DirectX11: return "DirectX11";
#endif
		default: break;
	}
	LE_CORE_ASSERT(false, "Unknown render API.");
	return "";
}
