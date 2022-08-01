#pragma once
#include "../../CoreBase.hpp"

namespace LimeEngine
{
	class RenderingSystem;
	struct IDrawable;

	class RenderQueue
	{
	public:
		void Draw(RenderingSystem& renderingSystem);
		void Sort(const Vector& target);
		void Add(IDrawable* drawable);
		bool Remove(const IDrawable* drawable);

	private:
		std::vector<IDrawable*> queue;
	};
}