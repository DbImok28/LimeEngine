// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "SceneObject.hpp"
#include "Scene/Components/MeshComponent.hpp"

namespace LimeEngine
{
	class MeshObject : public SceneObject
	{
	public:
		explicit MeshObject(const std::string& objectName = "MeshObject");

		void SetMesh(const ResourcePath& resourcePath);
		void SetMesh(GameResourceRef<Mesh> mesh);

		MeshComponent* meshComponent;
	};
}
