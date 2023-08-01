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
		explicit MeshObject(
			Engine* engine, const std::string& objectName = "MeshObject", const Transform& transform = {}, const ResourcePath& meshResourcePath = "Engine\\NullMesh");
		MeshObject(Engine* engine, GameResourceRef<Mesh> mesh, const std::string& objectName = "MeshObject", const Transform& transform = {});
	};
}