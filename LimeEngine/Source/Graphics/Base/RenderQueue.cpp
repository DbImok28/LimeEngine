#include "lepch.hpp"
#include "RenderQueue.hpp"
#include "Graphics/Renderer.hpp"

namespace LimeEngine
{
	void RenderQueue::Draw(Renderer& renderer)
	{
		for (auto& drawable : queue)
		{
			drawable->Draw(renderer);
		}
	}
	void RenderQueue::Sort(const Vector& target)
	{
		std::sort(std::begin(queue), std::end(queue), [&target](IDrawable* d1, IDrawable* d2) { return d1->GetDistance(target) > d2->GetDistance(target); });
	}
	void RenderQueue::Add(IDrawable* drawable)
	{
		if (!drawable) return;
		queue.push_back(drawable);
	}
	bool RenderQueue::Remove(const IDrawable* drawable)
	{
		if (!drawable) return false;
		return queue.erase(std::find(std::begin(queue), std::end(queue), drawable)) != std::end(queue);
	}
}