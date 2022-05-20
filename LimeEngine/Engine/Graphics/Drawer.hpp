#pragma once
#include <list>
#include "../Scene/MeshComponent.hpp"

namespace LimeEngine
{
	class Drawer
	{
	public:
		void AddToRender(MeshComponent* mesh);
		bool RemoveFromRender(const MeshComponent* mesh);
		void Render(const CameraComponent* camera);
	public:
		std::list<MeshComponent*> meshes;
	};
}