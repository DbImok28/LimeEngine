#pragma once
#include "SceneComponent.hpp"
#include "../Graphics/Base/Mesh.hpp"
#include "../Graphics/Base/IDrawable.hpp"

namespace LimeEngine
{
	class MeshComponent : public SceneComponent, IDrawable
	{
	public:
		explicit MeshComponent(Engine* engine, const Transform& transform = {}, size_t id = 0);
		virtual ~MeshComponent() override;

		void SetVisibility(bool visibility);
		void ShowMesh();
		void HideMesh();

		virtual void Draw(RenderingSystem& renderingSystem) override;
		virtual float GetDistance(const Vector& target) noexcept override;

	public:
		Mesh* mesh = nullptr;

	private:
		bool isVisible = false;
	};
}