#include "EngineLayer.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	LE_DEFINE_LOGGER(LogEngineLayer);

	Engine* EngineLayer::GetEngine()
	{
		return Engine::GetEngine();
	}
}
