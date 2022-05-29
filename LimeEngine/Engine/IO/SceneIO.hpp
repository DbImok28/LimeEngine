#pragma once
#include "../Scene/CameraComponent.hpp"

namespace LimeEngine
{
	class SceneIO
	{
	public:
		SceneIO();
		SceneIO(CameraComponent* camera);
		CameraComponent* camera;
	};
}