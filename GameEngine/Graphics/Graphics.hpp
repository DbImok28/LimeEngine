#pragma once
#include "../Exceptions/EngineExceptions.hpp"

#define GFX_EXCEPTION(hr) Window::WindowException(__LINE__, __FILE__, hr)

class Graphics
{
public:
	Graphics();
	class GraphicsException : public HrException
	{
	public:
		GraphicsException(int line, const char* file, HRESULT hr) noexcept;
		const wchar_t* GetType() const noexcept override;
	};

	void RenderFrame();
private:
	void PreProcessing();
	void Processing();
	void PostProcessing();
};