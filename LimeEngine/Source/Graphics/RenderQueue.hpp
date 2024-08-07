// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

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
