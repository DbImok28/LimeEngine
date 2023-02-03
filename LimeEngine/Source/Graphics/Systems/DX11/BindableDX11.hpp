#pragma once
#include "DirectXDef.hpp"
#include "Graphics/IBindable.hpp"

namespace LimeEngine
{
	class RendererDX11;

	class BindableDX11 : public IBindable
	{
	public:
		explicit BindableDX11(RendererDX11& renderingSystem) : renderingSystem(renderingSystem) {}
		virtual ~BindableDX11() override = default;

	protected:
		ID3D11Device* GetDevice() const noexcept;
		ID3D11DeviceContext* GetDeviceContext() const noexcept;
		RendererDX11& GetRenderingSystem() const noexcept;

	private:
		RendererDX11& renderingSystem;
	};
}