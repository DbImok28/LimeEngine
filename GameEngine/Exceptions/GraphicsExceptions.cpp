#include "GraphicsExceptions.hpp"

GraphicsHrException::GraphicsHrException(int line, const char* file, HRESULT hr) noexcept : HrException(line, file, hr) {}

const wchar_t* GraphicsHrException::GetType() const noexcept
{
	return L"GraphicsHrException";
}

InfoGraphicsHrException::InfoGraphicsHrException(int line, const char* file, HRESULT hr, std::wstring info) noexcept : GraphicsHrException(line, file, hr), info(info) {}

InfoGraphicsHrException::InfoGraphicsHrException(int line, const char* file, HRESULT hr, std::vector<std::wstring> info) noexcept : GraphicsHrException(line, file, hr)
{
	std::wostringstream oss;
	for (auto&& str : info)
		oss << str;
	this->info = oss.str();
}

const wchar_t* InfoGraphicsHrException::GetType() const noexcept
{
	return L"InfoGraphicsHrException";
}

const wchar_t* InfoGraphicsHrException::what() const noexcept
{
	std::wostringstream oss;
	oss << GetType() << std::endl
		<< L"Info: " << info << std::endl
		<< HrErrorString()
		<< GetErrorLocation();
	buffer = oss.str();
	return buffer.c_str();
}

InfoGraphicsException::InfoGraphicsException(int line, const char* file, std::wstring info) noexcept : EngineException(line, file), info(info) {}

InfoGraphicsException::InfoGraphicsException(int line, const char* file, std::vector<std::wstring> info) noexcept : EngineException(line, file)
{
	std::wostringstream oss;
	for (auto&& str : info)
		oss << str;
	this->info = oss.str();
}

const wchar_t* InfoGraphicsException::GetType() const noexcept
{
	return L"InfoGraphicsException";
}

const wchar_t* InfoGraphicsException::what() const noexcept
{
	std::wostringstream oss;
	oss << GetType() << std::endl
		<< L"Info: " << info << std::endl
		<< GetErrorLocation();
	buffer = oss.str();
	return buffer.c_str();
}
