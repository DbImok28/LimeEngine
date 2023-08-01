// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

namespace LimeEngine
{
	class Engine;

	class EngineLayer
	{
	public:
		explicit EngineLayer(Engine* engine) : engine(engine) {}

		virtual void Update() = 0;

	protected:
		Engine* engine;
	};
}
