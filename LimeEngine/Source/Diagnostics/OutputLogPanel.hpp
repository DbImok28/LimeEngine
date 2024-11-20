// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "LoggerSink.hpp"

namespace LimeEngine
{
	class OutputLogPanel
	{
	public:
		OutputLogPanel() noexcept = default;
		explicit OutputLogPanel(Logger* logger, const std::string& title = "OutputLog", size_t maxMessages = 200) noexcept;
		~OutputLogPanel() noexcept;

		void SetLogger(Logger* logger, const std::string& title) noexcept;
		void SetLogger(Logger* newLogger) noexcept;
		void SetTitle(const std::string& title = "OutputLog") noexcept;

	public:
		void Render();

	private:
		std::string title;
		Logger* logger = nullptr;
		SRef<BufferedLogSink> sink;
	};
}
