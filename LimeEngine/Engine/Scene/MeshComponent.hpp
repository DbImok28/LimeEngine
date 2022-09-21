#pragma once
#include "SceneComponent.hpp"
#include "../Graphics/Base/Mesh.hpp"
#include "../Graphics/Base/IDrawable.hpp"

namespace LimeEngine
{
	class MeshComponent : public SceneComponent, IDrawable
	{
	public:
		explicit MeshComponent(Engine* engine, const Transform& transform = {}, std::string path = "Engine\\NullMesh");
		MeshComponent(Engine* engine, const Transform& transform, GameResourceRef<Mesh> mesh);
		virtual ~MeshComponent() override;

		void SetVisibility(bool visibility);
		void ShowMesh();
		void HideMesh();

		virtual void Draw(Renderer& renderer) override;
		virtual float GetDistance(const Vector& target) noexcept override;

	public:
		GameResourceRef<Mesh> mesh;

	private:
		bool isVisible = false;
	};
}