#pragma once
#include "SceneComponent.hpp"
#include "../Base/Mesh.hpp"

namespace LimeEngine
{
	class MeshComponent : public SceneComponent
	{
	public:
		MeshComponent(Engine* engine, Transform transform = {}, size_t id = 0) noexcept;
		// TODO: Remove this
		void Render(const CameraComponent* camera);
		void AddToRender();
		bool RemoveFromRender();
	protected:
		size_t id = 0;
		Mesh* mesh = nullptr;
	};
}