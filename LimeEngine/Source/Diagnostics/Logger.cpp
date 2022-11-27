#include "Logger.hpp"
#include <stdarg.h>
#include <iostream>
#include <chrono>

namespace LimeEngine
{
	const LogCategory Logger::LogDebug(TEXT("Debug"));
	const LogCategory Logger::LogTemp(TEXT("Temp"));
	const LogCategory Logger::LogEngine(TEXT("Engine"));
	const LogCategory Logger::LogGraphics(TEXT("Graphics"));

	const std::map<LogLevel, LogLevelDesc> Logger::ToLogLevelDesc = {
		{LogLevel::Trace,    { TEXT("Trace"), PrimaryColor::Gray }    },
        { LogLevel::Note,    { TEXT("Note"), PrimaryColor::White }    },
		{ LogLevel::Warning, { TEXT("Warning"), PrimaryColor::Yellow }},
        { LogLevel::Error,   { TEXT("Error"), PrimaryColor::Red }     },
		{ LogLevel::Debug,   { TEXT("Debug"), PrimaryColor::Green }   },
	};

	Logger::Logger(Console* console) : console(console), fileStream(GetOutFileName())
	{
		if (console && !this->console->Open(TEXT("Output"))) throw MSG_EXCEPTION("Error open console");
		if (!fileStream.is_open()) throw MSG_EXCEPTION("Log file opened fail");
	}

	Logger::~Logger() noexcept
	{
		if (console) console->Close();
		if (fileStream.is_open()) fileStream.close();
	}

	void Logger::CLog(LogLevel level, const TCHAR* format, ...) noexcept
	{
		TCHAR buf[256];
		va_list args;

		va_start(args, format);
		_vstprintf_s(buf, format, args);
		va_end(args);

		WriteFormatted(level, buf);
	}

	void Logger::CLog(LogLevel level, const LogCategory& category, const TCHAR* format, ...) noexcept
	{
		TCHAR buf[256];
		va_list args;

		va_start(args, format);
		_vstprintf_s(buf, format, args);
		va_end(args);

		WriteFormatted(level, category, buf);
	}

	void Logger::WriteFormatted(LogLevel level, tstring_view msg) noexcept
	{
		const auto& logLevelDesc = ToLogLevelDesc.find(level)->second;
		WriteLog(FormatLogMessage(msg, logLevelDesc), logLevelDesc.color);
	}

	void Logger::WriteFormatted(LogLevel level, const LogCategory& category, tstring_view msg) noexcept
	{
		const auto& logLevelDesc = ToLogLevelDesc.find(level)->second;
		WriteLog(FormatLogMessage(msg, logLevelDesc, category), logLevelDesc.color);
	}

	tstring Logger::FormatLogMessage(tstring_view msg, const LogLevelDesc& logLevelDesc) const noexcept
	{
		const auto now = std::chrono::system_clock::now();
		return std::format(TEXT("[{:%Y.%m.%d %H:%M:%OS %OM}][{}] {}\n"), now, logLevelDesc.name, msg);
	}

	tstring Logger::FormatLogMessage(tstring_view msg, const LogLevelDesc& logLevelDesc, const LogCategory& category) const noexcept
	{
		const auto now = std::chrono::system_clock::now();
		return std::format(TEXT("[{:%Y.%m.%d %H:%M:%OS %OM}][{}]{}: {}\n"), now, logLevelDesc.name, category.name, msg);
	}

	void Logger::WriteLog(tstring_view msg, PrimaryColor color) noexcept
	{
		WriteToConsole(msg, color);
		WriteToFile(msg);
		WriteToScreen(msg);
	}

	void Logger::WriteToConsole(tstring_view msg, PrimaryColor color) noexcept
	{
		if (console) console->Print(msg, color);
	}

	void Logger::WriteToFile(tstring_view msg) noexcept
	{
		if (fileStream.is_open()) fileStream << msg;
	}

	void Logger::WriteToScreen(tstring_view msg) noexcept
	{
		// TODO: Add log to screen
		auto msgToScreen = tstring(TEXT("<Screen> ")) + tstring(msg);
		if (console) console->Print(msgToScreen, PrimaryColor::Yellow);
	}

	tstring Logger::GetOutFileName() const noexcept
	{
		return TEXT("LastOutputLog.log");
	}
}