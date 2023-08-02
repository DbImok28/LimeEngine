// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "MeshObject.hpp"

namespace LimeEngine
{
	MeshObject::MeshObject(Engine* engine, const std::string& objectName) : SceneObject(engine, objectName)
	{
		meshComponent = SetupAttachment<MeshComponent>(engine, "MeshComponent");
	}

	void MeshObject::SetMesh(const ResourcePath& resourcePath)
	{
		meshComponent->SetMesh(resourcePath);
	}

	void MeshObject::SetMesh(GameResourceRef<Mesh> mesh)
	{
		meshComponent->SetMesh(mesh);
	}
}
