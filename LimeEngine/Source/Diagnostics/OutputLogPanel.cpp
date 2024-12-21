// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "OutputLogPanel.hpp"

namespace LimeEngine
{
	OutputLogPanel::OutputLogPanel(Logger* logger, const std::string& title, size_t maxMessages) noexcept :
		sink(MakeShared<BufferedLogSink>(maxMessages)), logger(logger), title(title)
	{
		if (logger) logger->AddSink(sink);
	}

	OutputLogPanel::~OutputLogPanel() noexcept
	{
		if (logger) logger->RemoveSink(sink);
	}

	void OutputLogPanel::Render()
	{
		if (RuntimeEditor::BeginPanel(title))
		{
			if (!sink)
				RuntimeEditor::Text("Logger is not set!");
			else
			{
				for (const auto& message : sink->GetMessages())
				{
					RuntimeEditor::SetTextColor(LogLevelToColor(message.level));
					RuntimeEditor::Text(message.msg);
					RuntimeEditor::ResetTextColor();
				}
			}
			RuntimeEditor::AutoScroll(true);
			RuntimeEditor::EndPanel();
		}
	}

	void OutputLogPanel::SetLogger(Logger* logger, const std::string& title) noexcept
	{
		SetLogger(logger);
		SetTitle(title);
	}

	void OutputLogPanel::SetLogger(Logger* newLogger) noexcept
	{
		if (logger) logger->RemoveSink(sink);

		logger = newLogger;
		if (logger) logger->AddSink(sink);
	}

	void OutputLogPanel::SetTitle(const std::string& title) noexcept
	{
		this->title = title;
	}

	SRef<BufferedLogSink> OutputLogPanel::GetSink() const
	{
		return sink;
	}
}
