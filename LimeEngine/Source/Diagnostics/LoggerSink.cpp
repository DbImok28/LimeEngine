// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "LoggerSink.hpp"

namespace LimeEngine
{
	LogLevel LogMessage::GetLogLevel() const
	{
		return static_cast<LogLevel>(logMsg.level);
	}

	std::string LogMessage::GetSourceMessage() const
	{
		return std::string(logMsg.payload);
	}

	std::string LogMessage::GetFormattedMessage(LoggerSink* sink) const
	{
		return sink->Format(*this);
	}

	LogLevel LogMessage::GetLevel() const
	{
		return static_cast<LogLevel>(logMsg.level);
	}

	std::chrono::system_clock::time_point LogMessage::GetTime() const
	{
		return logMsg.time;
	}

	size_t LogMessage::GetThreadId() const
	{
		return logMsg.thread_id;
	}

	// LoggerSink

	void LoggerSink::sink_it_(const spdlog::details::log_msg& msg)
	{
		Log(LogMessage(msg));
	}

	void LoggerSink::flush_()
	{
		Flush();
	}

	std::string LoggerSink::Format(const LogMessage& logMessage) const
	{
		std::string formatted;
		formatter_->format(logMessage.logMsg, formatted);
		return formatted;
	}

	// BufferedLogSink

	BufferedLogMessage::BufferedLogMessage(const std::string& msg, LogLevel level, const std::chrono::system_clock::time_point& time, size_t threadId) :
		msg(msg), level(level), time(time), threadId(threadId)
	{}

	BufferedLogSink::BufferedLogSink(size_t maxMessages) noexcept : maxMessages(maxMessages) {}

	void BufferedLogSink::Log(const LogMessage& logMessage)
	{
		messages.emplace_back(autoFormat ? Format(logMessage) : logMessage.GetSourceMessage(), logMessage.GetLogLevel(), logMessage.GetTime(), logMessage.GetThreadId());
		if (messages.size() > maxMessages) messages.pop_front();
	}

	const std::deque<BufferedLogMessage>& BufferedLogSink::GetMessages() const noexcept
	{
		return messages;
	}

	size_t BufferedLogSink::GetMaxMessages() const noexcept
	{
		return maxMessages;
	}

	void BufferedLogSink::SetMaxMessages(size_t maxMessages)
	{
		this->maxMessages = maxMessages;
		while (messages.size() > this->maxMessages)
			messages.pop_front();
	}
}
