#pragma once
#include "SceneComponent.hpp"
#include "../Graphics/Base/Mesh.hpp"

namespace LimeEngine
{
	class MeshComponent : public SceneComponent
	{
	public:
		MeshComponent(Engine* engine, Transform transform = {}, size_t id = 0) noexcept;
		virtual ~MeshComponent() override;
		void SetVisibility(bool visibility);
		void ShowMesh();
		void HideMesh();

	public:
		Mesh* mesh = nullptr;
		Material* material = nullptr;

	private:
		bool isVisible = false;
	};
}