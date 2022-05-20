#include "Drawer.hpp"

void LimeEngine::Drawer::AddToRender(MeshComponent* mesh)
{
	meshes.push_back(mesh);
}

bool LimeEngine::Drawer::RemoveFromRender(const MeshComponent* mesh)
{
	return meshes.erase(std::find(std::begin(meshes), std::end(meshes), mesh)) != std::end(meshes);
}

void LimeEngine::Drawer::Render(const CameraComponent* camera)
{
	for (auto& mesh : meshes)
	{
		mesh->Render(camera);
	}
}