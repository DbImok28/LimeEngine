// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "OutputLogPanel.hpp"

namespace LimeEngine
{
	OutputLogPanel::OutputLogPanel(const std::string& title, size_t maxMessages) noexcept : sink(MakeShared<BufferedLogSink>(maxMessages)), title(title)
	{
		LoggerManager::GetLoggerManager()->AddSink(sink);
	}

	OutputLogPanel::~OutputLogPanel() noexcept
	{
		LoggerManager::GetLoggerManager()->RemoveSink(sink);
	}

	void OutputLogPanel::Render()
	{
		LE_ASSERT(sink);
		
		if (RuntimeEditor::BeginPanel(title))
		{
			for (const auto& message : sink->GetMessages())
			{
				RuntimeEditor::SetTextColor(LogLevelToColor(message.level));
				RuntimeEditor::Text(message.msg);
				RuntimeEditor::ResetTextColor();
			}
			RuntimeEditor::AutoScroll(true);
			RuntimeEditor::EndPanel();
		}
	}

	SRef<BufferedLogSink> OutputLogPanel::GetSink() const
	{
		return sink;
	}
}
