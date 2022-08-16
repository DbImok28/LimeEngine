#pragma once
#include "../../CoreBase.hpp"

namespace LimeEngine
{
	class Renderer;
	struct IDrawable;

	class RenderQueue
	{
	public:
		void Draw(Renderer& renderer);
		void Sort(const Vector& target);
		void Add(IDrawable* drawable);
		bool Remove(const IDrawable* drawable);

	private:
		std::vector<IDrawable*> queue;
	};
}