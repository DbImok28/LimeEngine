#include "BindableDX11.hpp"
#include "RendererDX11.hpp"

namespace LimeEngine
{
	ID3D11Device* BindableDX11::GetDevice() const noexcept
	{
		return renderingSystem.device.Get();
	}

	ID3D11DeviceContext* BindableDX11::GetDeviceContext() const noexcept
	{
		return renderingSystem.deviceContext.Get();
	}

	RendererDX11& BindableDX11::GetRenderingSystem() const noexcept
	{
		return renderingSystem;
	}
}