#include "lepch.hpp"
#include "Renderer.hpp"

#ifdef LE_ENABLE_RENDER_API_DX11
	#include "Graphics/API/DX11/RendererDX11.hpp"
#endif

namespace LimeEngine
{
	std::unique_ptr<Renderer> Renderer::Create(RenderAPI api, Window& window, DisplayMode mode)
	{
		switch (api)
		{
			case LimeEngine::RenderAPI::Auto: [[fallthrough]];
#if defined(LE_ENABLE_RENDER_API_DX11)
			case LimeEngine::RenderAPI::DirectX11: return std::make_unique<RendererDX11>(window, mode); break;
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API. Failed to create renderer.");
		return nullptr;
	}

	Renderer::Renderer(std::unique_ptr<RenderOutput>&& renderOutput) : renderOutput(std::move(renderOutput)) {}

	const CameraComponent* Renderer::GetCamera() const noexcept
	{
		return camera;
	}

	void Renderer::SetCamera(CameraComponent* camera) noexcept
	{
		this->camera = camera;
	}

	DisplayMode Renderer::GetDisplayMode() const noexcept
	{
		return renderOutput->GetDisplayMode();
	}

	void Renderer::SetDisplayMode(DisplayMode mode)
	{
		renderOutput->SetDisplayMode(mode);
	}

	void Renderer::AddToRender(IDrawable* drawable)
	{
		renderQueue.Add(drawable);
	}

	void Renderer::RemoveFromRender(const IDrawable* drawable) noexcept
	{
		renderQueue.Remove(drawable);
	}
}