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
