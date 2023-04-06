#pragma once
#include "EngineLayer.hpp"

namespace LimeEngine
{
	class EditorLayer : public EngineLayer
	{
		LE_DELETE_COPY(EditorLayer)

	public:
		explicit EditorLayer(Engine* engine);

		void Update() override;
	};
}
