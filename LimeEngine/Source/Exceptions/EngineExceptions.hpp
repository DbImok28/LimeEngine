#pragma once
#include "CoreBase.hpp"

#define MSG_EXCEPTION(msg) LimeEngine::EngineException(__LINE__, __FILE__, msg)

namespace LimeEngine
{
	class EngineException : public std::exception
	{
	public:
		EngineException(int line, const char* file) noexcept;
		EngineException(int line, const char* file, const std::string& info) noexcept;
		EngineException(int line, const char* file, const std::vector<std::string>& info) noexcept;

		virtual const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		int GetLine() const noexcept;
		const std::string& GetFile() const noexcept;
		std::string GetErrorLocation() const noexcept;
		std::string GetErrorInfo() const noexcept;

	private:
		int line;
		std::string file;
		std::string info;

	protected:
		mutable std::string buffer;
	};
}