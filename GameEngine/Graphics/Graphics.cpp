#include "Graphics.hpp"

Graphics::GraphicsException::GraphicsException(int line, const char* file, HRESULT hr) noexcept : HrException(line, file, hr) {}

const wchar_t* Graphics::GraphicsException::GetType() const noexcept
{
	return L"GraphicsException";
}

Graphics::Graphics()
{
}

void Graphics::RenderFrame()
{
	PreProcessing();
	Processing();
	PostProcessing();
}

void Graphics::PreProcessing()
{
	
}

void Graphics::Processing()
{

}

void Graphics::PostProcessing()
{

}