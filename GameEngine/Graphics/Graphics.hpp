#pragma once
#include "../Exceptions/EngineExceptions.hpp"
#include "../Window/Window.hpp"

#define GFX_EXCEPTION(hr) Window::WindowException(__LINE__, __FILE__, hr)

class Graphics
{
public:
	class GraphicsException : public HrException
	{
	public:
		GraphicsException(int line, const char* file, HRESULT hr) noexcept;
		const wchar_t* GetType() const noexcept override;
	};
};