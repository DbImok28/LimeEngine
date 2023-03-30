#pragma once
#include "SceneComponent.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/IDrawable.hpp"

namespace LimeEngine
{
	class MeshComponent : public SceneComponent, IDrawable
	{
	public:
		explicit MeshComponent(
			Engine* engine, const std::string& componentName = "MeshComponent", const Transform& transform = {}, const ResourcePath& resourcePath = "Engine\\NullMesh");
		MeshComponent(Engine* engine, GameResourceRef<Mesh> mesh, const std::string& componentName = "MeshComponent", const Transform& transform = {});
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