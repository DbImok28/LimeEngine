// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "BindableDX11.hpp"

namespace LimeEngine
{
	enum class MaterialType;

	class VertexShaderDX11 : public BindableDX11
	{
	public:
		explicit VertexShaderDX11(RendererDX11& renderer) noexcept;
		VertexShaderDX11(RendererDX11& renderer, const FPath& filePath, MaterialType materialType);

		void Initialize(const FPath& filePath, MaterialType materialType);
		virtual void Bind() noexcept override;
		std::vector<D3D11_INPUT_ELEMENT_DESC> MakeInputLayout(MaterialType materialType) const;
		ID3D11VertexShader* GetShader() const noexcept;
		ID3D10Blob* GetBuffer() const noexcept;
		ID3D11InputLayout* GatInputLoyout() const noexcept;

	private:
		com_ptr<ID3D11VertexShader> shader = nullptr;
		com_ptr<ID3D10Blob> shaderBuffer = nullptr;
		com_ptr<ID3D11InputLayout> inputLoyout = nullptr;
	};

	class PixelShaderDX11 : public BindableDX11
	{
	public:
		explicit PixelShaderDX11(RendererDX11& renderer) noexcept;
		PixelShaderDX11(RendererDX11& renderer, const FPath& filePath);

		void Initialize(const FPath& filePath);
		virtual void Bind() noexcept override;
		ID3D11PixelShader* GetShader() const noexcept;
		ID3D10Blob* GetBuffer() const noexcept;

	private:
		com_ptr<ID3D11PixelShader> shader = nullptr;
		com_ptr<ID3D10Blob> shaderBuffer = nullptr;
	};
}