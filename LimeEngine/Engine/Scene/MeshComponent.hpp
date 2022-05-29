#pragma once
#include "SceneComponent.hpp"
#include "../Graphics/Base/Mesh.hpp"

namespace LimeEngine
{
	class MeshComponent : public SceneComponent
	{
	public:
		MeshComponent(Engine* engine, Transform transform = {}, size_t id = 0) noexcept;
		void AddToRender();
		bool RemoveFromRender();

	public:
		Mesh* mesh = nullptr;
	};
}