// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Console.hpp"
#include "Platform/Platform.hpp"

namespace LimeEngine
{
	URef<Console> Console::Create(const ConsoleArgs& args)
	{
		return Platform::MakeConsole(args);
	}

	LoggerConsole::LoggerConsole(Console* console, ConsoleLogSink::ColorMode colorMode) noexcept : sink(std::make_shared<ConsoleLogSink>(console->GetHandle(), colorMode))
	{
		LoggerManager::GetLoggerManager()->AddSink(sink);
	}

	LoggerConsole::~LoggerConsole() noexcept
	{
		LoggerManager::GetLoggerManager()->RemoveSink(sink);
	}
}
