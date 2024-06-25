// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#pragma once
#include "Graphics/RenderTarget.hpp"
#include "DirectXDef.hpp"

namespace LimeEngine
{
	class DepthStencilDX11 : public DepthStencil
	{
	public:
		DepthStencilDX11() = default;
		DepthStencilDX11(uint width, uint height);

		void Initialize(uint width, uint height);

	public:
		virtual void Clear(float clearDepth = 1.0f, uint8 clearStencil = 0u) override;
		virtual void ClearDepth(float clearDepth = 1.0f) override;
		virtual void ClearStencil(uint clearStencil = 0u) override;
		virtual void Resize(uint width, uint height) override;
		virtual void Reset() override;

		virtual URef<Texture2D> GetTexture() override;

		ID3D11Texture2D* GetTextureBuffer() const noexcept;
		ID3D11DepthStencilView* GetView() const noexcept;
		ID3D11DepthStencilView* const* GetViewAddress() const noexcept;

	private:
		com_ptr<ID3D11DepthStencilView> depthStencilTextureView = nullptr;
		com_ptr<ID3D11Texture2D> depthStencilTexture = nullptr;
	};

	class RenderTargetDX11 : public RenderTarget
	{
	public:
		RenderTargetDX11() = default;
		RenderTargetDX11(uint width, uint height);

		void Initialize(uint width, uint height);

	public:
		virtual void Bind(DepthStencil* depthStencil = nullptr) override;
		virtual void Clear(const float* clearColor) override;
		virtual bool Resize(uint width, uint height) override;
		virtual void Reset() override;

		virtual URef<Texture2D> GetTexture() override;

		ID3D11Texture2D* GetTextureBuffer() const noexcept;
		ID3D11RenderTargetView* GetView() const noexcept;
		ID3D11RenderTargetView* const* GetViewAddress() const noexcept;

	private:
		com_ptr<ID3D11Texture2D> renderTargetTexture = nullptr;
		com_ptr<ID3D11RenderTargetView> renderTargetView = nullptr;
	};

	class WindowRenderTargetDX11 : public RenderTarget
	{
	public:
		WindowRenderTargetDX11() = default;
		WindowRenderTargetDX11(ID3D11Texture2D* outTexture) {}

		void Initialize(ID3D11Texture2D* outTexture);

	public:
		virtual void Bind(DepthStencil* depthStencil = nullptr) override;
		virtual void Clear(const float* clearColor) override;
		virtual bool Resize(uint width, uint height) override;
		virtual void Reset() override;

		virtual URef<Texture2D> GetTexture() override;

		ID3D11Texture2D* GetTextureBuffer() const noexcept;
		ID3D11RenderTargetView* GetView() const noexcept;
		ID3D11RenderTargetView* const* GetViewAddress() const noexcept;

	private:
		ID3D11Texture2D* renderTargetTexture = nullptr;
		com_ptr<ID3D11RenderTargetView> renderTargetView = nullptr;
	};
}
