#include "BindableDX11.hpp"
#include "RenderingSystemDX11.hpp"

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

	RenderingSystemDX11& BindableDX11::GetRenderingSystem() const noexcept
	{
		return renderingSystem;
	}
}