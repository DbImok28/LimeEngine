#pragma once
#include "SceneMap.hpp"
#include "DefaultPlayerCameraComponent.hpp"

namespace LimeEngine
{
	class Scene
	{
	private:
		void Update();
		void Render();
	public:
		Scene(Engine* engine);
		Scene(Engine* engine, bool autoLoad);
		void Load();

		void UpdateScene();
		void RenderScene();
		void AttachMap(std::unique_ptr<SceneMap>&& map);
		bool CameraIsSet() const noexcept;
		CameraComponent* GetCamera() const noexcept;
		void SetCamera(CameraComponent* value) noexcept;
	public:
		std::vector<std::unique_ptr<SceneMap>> maps;
	private:
		CameraComponent* activeCamera = nullptr;
		Engine* engine = nullptr;
	};
}