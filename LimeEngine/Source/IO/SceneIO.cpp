#include "lepch.hpp"
#include "SceneIO.hpp"

namespace LimeEngine
{
	SceneIO::SceneIO() : camera(nullptr) {}

	SceneIO::SceneIO(CameraComponent* camera) : camera(camera) {}
}