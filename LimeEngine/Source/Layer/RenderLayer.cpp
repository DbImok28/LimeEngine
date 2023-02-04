#pragma once
#include "lepch.hpp"
#include "RenderLayer.hpp"

namespace LimeEngine
{
	RenderLayer::RenderLayer(Engine* engine, std::unique_ptr<Renderer>&& renderer, const RenderPreset& preset) :
		EngineLayer(engine), renderer(std::move(renderer)), presets({ preset })
	{}

	void RenderLayer::Update()
	{
		renderer->Render(presets[0]);
	}

	CameraComponent* RenderLayer::GetRenderCamera(size_t id) noexcept
	{
		if (id < presets.size())
		{
			return presets[id].camera;
		}
		return nullptr;
	}

	bool RenderLayer::SetRenderCamera(size_t id, CameraComponent* camera) noexcept
	{
		if (id < presets.size())
		{
			presets[id].camera = camera;
			return true;
		}
		return false;
	}

	Window* RenderLayer::GetRenderWindow(size_t id) noexcept
	{
		if (id < presets.size())
		{
			return presets[id].window;
		}
		return nullptr;
	}

	bool RenderLayer::SetRenderWindow(size_t id, Window* window) noexcept
	{
		if (id < presets.size())
		{
			presets[id].window = window;
			return true;
		}
		return false;
	}

	void RenderLayer::AddToRender(IDrawable* drawable)
	{
		renderer->AddToRender(drawable);
	}

	void RenderLayer::RemoveFromRender(const IDrawable* drawable) noexcept
	{
		renderer->RemoveFromRender(drawable);
	}

	const GraphicFactory* RenderLayer::GetGraphicFactory() noexcept
	{
		return renderer->GetGraphicFactory();
	}
}