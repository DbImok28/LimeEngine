#include "RenderIO.hpp"

namespace LimeEngine
{
	RenderIO::RenderIO(Renderer* renderer) : renderer(renderer) {}

	std::optional<int> RenderIO::Process()
	{
		if (renderer) return renderer->Process();
		return -1;
	}

	void RenderIO::Render()
	{
		if (renderer) renderer->Render();
	}
}