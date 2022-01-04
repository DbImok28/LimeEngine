#pragma once
#include "SceneComponent.hpp"
#include "../Base/Mesh.hpp"

namespace LimeEngine
{
	class MeshComponent : public SceneComponent
	{
	public:
		MeshComponent(Engine* engine, Transform transform = {}, size_t id = 0) noexcept;
		void Render() override;
		size_t id = 0;
		Mesh* mesh = nullptr;
	};
}