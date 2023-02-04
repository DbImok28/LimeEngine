#pragma once
#include "EngineLayer.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/RenderPreset.hpp"

namespace LimeEngine
{
	class RenderLayer : public EngineLayer
	{
	public:
		RenderLayer(Engine* engine, std::unique_ptr<Renderer>&& renderer, const RenderPreset& preset);

		void Update() override;
		void AddToRender(IDrawable* drawable);
		void RemoveFromRender(const IDrawable* drawable) noexcept;

		CameraComponent* GetRenderCamera(size_t id) noexcept;
		Window* GetRenderWindow(size_t id) noexcept;
		bool SetRenderCamera(size_t id, CameraComponent* camera) noexcept;
		bool SetRenderWindow(size_t id, Window* window) noexcept;

		const GraphicFactory* GetGraphicFactory() noexcept;

	private:
		std::vector<RenderPreset> presets;
		std::unique_ptr<Renderer> renderer;
	};
}