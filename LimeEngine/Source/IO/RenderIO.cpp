#include "lepch.hpp"
#include "RenderIO.hpp"

namespace LimeEngine
{
	RenderIO::RenderIO(Renderer* renderer) : renderer(renderer) {}

	void RenderIO::Process()
	{
		renderer->Process();
	}

	void RenderIO::Render()
	{
		if (renderer) renderer->Render();
	}
}