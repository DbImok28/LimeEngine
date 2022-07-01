#pragma once
#include "../Scene/CameraComponent.hpp"

namespace LimeEngine
{
	class SceneIO
	{
	public:
		SceneIO();
		explicit SceneIO(CameraComponent* camera);
		CameraComponent* camera;
	};
}