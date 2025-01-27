// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Logger.hpp"

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

	class LoggerSink : public spdlog::sinks::base_sink<spdlog::details::null_mutex>
	{
	private:
		virtual void sink_it_(const spdlog::details::log_msg& msg) final;
		virtual void flush_() final;

	public:
		virtual void Log(const LogMessage& logMessage) = 0;
		virtual void Flush() = 0;

		std::string Format(const LogMessage& logMessage) const;
	};

	class BufferedLogMessage
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

	class BufferedLogSink final : public LoggerSink
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
}
