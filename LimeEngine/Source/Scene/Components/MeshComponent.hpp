// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "SceneComponent.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/IDrawable.hpp"

namespace LimeEngine
{
	class MeshComponent : public SceneComponent, IDrawable
	{
	public:
		explicit MeshComponent(Engine* engine, const std::string& componentName = "MeshComponent");
		~MeshComponent();

		void SetMesh(const ResourcePath& resourcePath);
		void SetMesh(GameResourceRef<Mesh> mesh);
		void SetVisibility(bool visibility);
		void ShowMesh();
		void HideMesh();

		virtual void Draw(Renderer& renderer) override;
		virtual float GetDistance(const Vector& target) noexcept override;

	protected:
		virtual void DebugUpdate() override;

	public:
		GameResourceRef<Mesh> mesh;

	private:
		bool isVisible = false;
	};
}