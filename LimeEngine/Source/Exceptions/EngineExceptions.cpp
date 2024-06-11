// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "EngineExceptions.hpp"

namespace LimeEngine
{
	EngineException::EngineException(int line, const char* file) noexcept : line(line), file(file) {}

	EngineException::EngineException(int line, const char* file, const std::string& info) noexcept : line(line), file(file), info(info) {}

	EngineException::EngineException(int line, const char* file, const std::vector<std::string>& info) noexcept : line(line), file(file)
	{
		std::ostringstream oss;
		for (auto&& str : info)
			oss << str << std::endl;
		this->info = oss.str();
	}

	const char* EngineException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl << GetErrorInfo() << GetErrorLocation();
		buffer = oss.str();
		return buffer.c_str();
	}

	const char* EngineException::GetType() const noexcept
	{
		return "EngineException";
	}

	int EngineException::GetLine() const noexcept
	{
		return line;
	}

	const std::string& EngineException::GetFile() const noexcept
	{
		return file;
	}

	std::string EngineException::GetErrorLocation() const noexcept
	{
		std::ostringstream oss;
		oss << "File: " << file.c_str() << std::endl << "Line: " << line << std::endl;
		return oss.str();
	}

	std::string EngineException::GetErrorInfo() const noexcept
	{
		if (info.empty()) return {};
		std::ostringstream oss;
		oss << "Info: " << info << std::endl;
		return oss.str();
	}
}
