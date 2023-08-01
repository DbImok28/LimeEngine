// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
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
