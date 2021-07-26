#pragma once
#include <exception>
#include <string>

class EngineException // : public std::exception
{
public:
	/*"Use Info() instead of what()!"
	const char* what() const noexcept override final;*/

	EngineException(int line, const char* file) noexcept;
	virtual const wchar_t* what() const noexcept;
	virtual const wchar_t* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetErrorLocation() const noexcept;
private:
	int line;
	std::string file;
protected:
	mutable std::wstring buffer;
};