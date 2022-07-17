#include "Logger.hpp"
#include <stdarg.h>
#include <iostream>
#include <chrono>

namespace LimeEngine
{
	const std::map<LogLevel, LogLevelDesc> Logger::ToLogLevelDesc = {
		{LogLevel::Trace,    { TEXT("Trace"), PrimaryColor::Gray }    },
        { LogLevel::Note,    { TEXT("Note"), PrimaryColor::White }    },
		{ LogLevel::Warning, { TEXT("Warning"), PrimaryColor::Yellow }},
        { LogLevel::Error,   { TEXT("Error"), PrimaryColor::Red }     },
		{ LogLevel::Debug,   { TEXT("Debug"), PrimaryColor::Green }   },
	};

	Logger::Logger(Console* console) : console(console), fileStream(GetOutFileName())
	{
		if (!this->console->Open(TEXT("Output"))) throw MSG_EXCEPTION("Error open console");
		if (!fileStream.is_open()) throw MSG_EXCEPTION("Log file opened fail");
	}

	Logger::~Logger() noexcept
	{
		console->Close();
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
		auto& logLevelDesc = ToLogLevelDesc.find(level)->second;
		WriteLog(FormatLog(msg, logLevelDesc), logLevelDesc.color);
	}

	void Logger::WriteFormatted(LogLevel level, const LogCategory& category, tstring_view msg) noexcept
	{
		auto& logLevelDesc = ToLogLevelDesc.find(level)->second;
		WriteLog(FormatLog(msg, logLevelDesc, category), logLevelDesc.color);
	}

	tstring Logger::FormatLog(tstring_view msg, const LogLevelDesc& logLevelDesc) noexcept
	{
		const auto now = std::chrono::system_clock::now();
		return std::format(TEXT("[{:%Y.%m.%d %H:%M:%OS %OM}][{}] {}\n"), now, logLevelDesc.name, msg);
	}

	tstring Logger::FormatLog(tstring_view msg, const LogLevelDesc& logLevelDesc, const LogCategory& category) noexcept
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
		console->Print(msg, color);
	}

	void Logger::WriteToFile(tstring_view msg) noexcept
	{
		if (fileStream.is_open()) fileStream << msg;
	}

	void Logger::WriteToScreen(tstring_view msg) noexcept
	{
		// TODO: Add log to screen
		std::cout << "<Screen> " << msg;
	}

	tstring Logger::GetOutFileName() const noexcept
	{
		return TEXT("LastOutputLog.log");
	}
}