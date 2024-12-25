// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "EngineLayer.hpp"
#include "Diagnostics/OutputLogPanel.hpp"

namespace LimeEngine
{
	class EditorLayer : public EngineLayer
	{
		LE_DELETE_COPY(EditorLayer)

	public:
		EditorLayer() noexcept : EngineLayer("EditorLayer"), outputLogPanel(Logger::GetCoreLogger()) {}
		static EditorLayer& GetEditorLayer();

		virtual void Update() override;
		virtual void DebugUpdate() override;

	private:
		OutputLogPanel outputLogPanel;
	};
}
