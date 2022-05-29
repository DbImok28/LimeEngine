#include "RenderIO.hpp"

namespace LimeEngine
{
	RenderIO::RenderIO(Renderer* renderer) : renderer(renderer) {}

	std::optional<int> RenderIO::Process()
	{
		if (renderer != nullptr)
			return renderer->Process();
		return -1;
	}

	void RenderIO::Render(const CameraComponent* cameraComponent)
	{
		if (renderer != nullptr)
			renderer->Render(cameraComponent);
	}
}