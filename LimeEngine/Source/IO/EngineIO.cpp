#include "EngineIO.hpp"

namespace LimeEngine
{
	EngineIO::EngineIO(RenderIO&& renderIO, SceneIO&& sceneIO) : renderIO(std::move(renderIO)), sceneIO(std::move(sceneIO)) {}

	std::optional<int> EngineIO::Process()
	{
		return renderIO.Process();
	}

	void EngineIO::Render()
	{
		renderIO.Render();
	}

	void EngineIO::SetInputCamera(CameraComponent* camera)
	{
		sceneIO.camera = camera;
		renderIO.renderer->SetInputCamera(camera);
	}

	InputDevice& EngineIO::GetInput() noexcept
	{
		return renderIO.renderer->GetInputDevice();
	}
}