#pragma once
#include "SceneComponent.hpp"
#include "../Base/Mesh.hpp"

namespace LimeEngine
{
	class MeshComponent : public SceneComponent
	{
	public:
		MeshComponent(size_t id = 0) noexcept;
		void Initialize(Engine* engine, Transformable* rootTransform) override;
		void Render() override;
		size_t id = 0;
		Mesh* mesh = nullptr;
	};
}