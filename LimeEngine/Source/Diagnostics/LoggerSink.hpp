// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Logger.hpp"
#include <spdlog/sinks/basic_file_sink.h>

#ifdef _WIN32
	#include <spdlog/sinks/wincolor_sink.h>
#else
	#include <spdlog/sinks/ansicolor_sink.h>
#endif

#ifdef _WIN32
using BaseConsoleLogSinkST = spdlog::sinks::wincolor_sink<spdlog::details::console_nullmutex>;
using BaseConsoleLogSinkMT = spdlog::sinks::wincolor_sink<spdlog::details::console_mutex>;
#else
using BaseConsoleLogSinkST = spdlog::sinks::ansicolor_sink<spdlog::details::console_nullmutex>;
using BaseConsoleLogSinkMT = spdlog::sinks::wincolor_sink<spdlog::details::console_mutex>;
#endif

namespace LimeEngine
{
	class LoggerSink;

	class LogMessage
	{
		friend LoggerSink;

	public:
		explicit LogMessage(const spdlog::details::log_msg& logMsg) : logMsg(logMsg) {}

		LogLevel GetLogLevel() const;
		std::string GetSourceMessage() const;
		std::string GetFormattedMessage(LoggerSink* sink) const;
		LogLevel GetLevel() const;
		std::chrono::system_clock::time_point GetTime() const;
		size_t GetThreadId() const;

	private:
		spdlog::details::log_msg logMsg;
	};

	class LE_API LoggerSink : public spdlog::sinks::base_sink<spdlog::details::null_mutex>
	{
	private:
		virtual void sink_it_(const spdlog::details::log_msg& msg) final;
		virtual void flush_() final;

	public:
		virtual void Log(const LogMessage& logMessage) = 0;
		virtual void Flush() = 0;

		std::string Format(const LogMessage& logMessage) const;
	};

	class LE_API BufferedLogMessage
	{
		friend LoggerSink;

	public:
		BufferedLogMessage() = default;
		BufferedLogMessage(const std::string& msg, LogLevel level, const std::chrono::system_clock::time_point& time, size_t threadId);

	public:
		std::string msg;
		LogLevel level;
		std::chrono::system_clock::time_point time;
		size_t threadId = 0;
	};

	class LE_API BufferedLogSink final : public LoggerSink
	{
	public:
		explicit BufferedLogSink(size_t maxMessages = 200) noexcept;

	protected:
		virtual void Log(const LogMessage& logMessage) override;
		virtual void Flush() override {}

	public:
		const std::deque<BufferedLogMessage>& GetMessages() const noexcept;
		size_t GetMaxMessages() const noexcept;
		void SetMaxMessages(size_t maxMessages);

	private:
		std::deque<BufferedLogMessage> messages;
		size_t maxMessages;

	public:
		bool autoFormat = true;
	};

	//using ConsoleLogSink = spdlog::sinks::stdout_color_sink_mt;

	class LE_API ConsoleLogSink final : public BaseConsoleLogSinkMT
	{
	public:
		using Supper = BaseConsoleLogSinkMT;

		enum class ColorMode
		{
			Always,
			Automatic,
			Never
		};

		explicit ConsoleLogSink(void* consoleHandle, ConsoleLogSink::ColorMode colorMode = ColorMode::Automatic) noexcept :
			Supper(consoleHandle, static_cast<spdlog::color_mode>(colorMode))
		{}
	};
}
