// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "LoggerSink.hpp"

namespace LimeEngine
{
	class LE_API OutputLogPanel
	{
	public:
		explicit OutputLogPanel(const std::string& title = "OutputLog", size_t maxMessages = 200) noexcept;
		~OutputLogPanel() noexcept;

		void Render();

		SRef<BufferedLogSink> GetSink() const;

	private:
		std::string title;
		SRef<BufferedLogSink> sink;
	};
}
