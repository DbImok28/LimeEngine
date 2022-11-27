// Copyright (C) 2022 Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Window/Base/Console.hpp"
#include <type_traits>
#include <format>
#include <map>
#include <fstream>

namespace LimeEngine
{
	// This is the string that checks for correct formatting at compile time (for std::format)
	template <class... _Args>
	using _Fmt_tstring = std::_Basic_format_string<TCHAR, std::type_identity_t<_Args>...>;

	enum class LogLevel
	{
		Trace,
		Note,
		Warning,
		Error,
		Debug
	};

	struct LogLevelDesc
	{
		tstring name;
		PrimaryColor color;
	};

	struct LogCategory
	{
		tstring name;
	};

	class Logger
	{
	public:
		static const LogCategory LogDebug;
		static const LogCategory LogTemp;
		static const LogCategory LogEngine;
		static const LogCategory LogGraphics;

		~Logger() noexcept;
		Logger(const Logger&) = default;
		Logger(Logger&&) noexcept = default;
		Logger& operator=(const Logger&) = default;
		Logger& operator=(Logger&&) noexcept = default;
		explicit Logger(Console* console = nullptr);

		template <typename... TArgs>
		void Log(LogLevel level, const _Fmt_tstring<TArgs...> format, TArgs&&... args) noexcept
		{
			WriteFormatted(level, std::format(format, std::forward<TArgs>(args)...));
		}
		template <typename... TArgs>
		void DynamicLog(LogLevel level, tstring_view format, TArgs&&... args)
		{
			WriteFormatted(level, std::vformat(format, std::make_format_args(args...)));
		}
		template <typename... TArgs>
		void Log(LogLevel level, const LogCategory& category, const _Fmt_tstring<TArgs...> format, TArgs&&... args) noexcept
		{
			WriteFormatted(level, category, std::format(format, std::forward<TArgs>(args)...));
		}
		template <typename... TArgs>
		void DynamicLog(LogLevel level, const LogCategory& category, tstring_view format, TArgs&&... args)
		{
			WriteFormatted(level, category, std::vformat(format, std::make_format_args(args...)));
		}
		void CLog(LogLevel level, const TCHAR* format, ...) noexcept;
		void CLog(LogLevel level, const LogCategory& category, const TCHAR* format, ...) noexcept;

		void WriteFormatted(LogLevel level, tstring_view msg) noexcept;
		void WriteFormatted(LogLevel level, const LogCategory& category, tstring_view msg) noexcept;
		tstring FormatLogMessage(tstring_view msg, const LogLevelDesc& logLevelDesc) const noexcept;
		tstring FormatLogMessage(tstring_view msg, const LogLevelDesc& logLevelDesc, const LogCategory& category) const noexcept;
		void WriteLog(tstring_view msg, PrimaryColor color) noexcept;
		void WriteToConsole(tstring_view msg, PrimaryColor color) noexcept;
		void WriteToFile(tstring_view msg) noexcept;
		void WriteToScreen(tstring_view msg) noexcept;
		tstring GetOutFileName() const noexcept;

	private:
		Console* console = nullptr;
		tofstream fileStream;
		static const std::map<LogLevel, LogLevelDesc> ToLogLevelDesc;
	};
}