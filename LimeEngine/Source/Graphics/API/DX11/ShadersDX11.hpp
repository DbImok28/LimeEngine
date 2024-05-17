// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "RendererDX11.hpp"
#include "Graphics/Shaders.hpp"

namespace LimeEngine
{
	DXGI_FORMAT ConvertToDX11ShaderDataType(ShaderDataType type);

	std::vector<D3D11_INPUT_ELEMENT_DESC> ConvertToDX11InputLayout(const InputLayout& inputLayout);

	class VertexShaderDX11 : public VertexShader
	{
	public:
		explicit VertexShaderDX11() noexcept;
		VertexShaderDX11(const FPath& filePath, const InputLayout& inputLayout);

		void Initialize(const FPath& filePath, const InputLayout& inputLayout);
		virtual void Bind() noexcept override;

		ID3D11VertexShader* GetShader() const noexcept;
		ID3D10Blob* GetBuffer() const noexcept;
		ID3D11InputLayout* GetInputLoyoutDX11() const noexcept;

	private:
		com_ptr<ID3D11VertexShader> shader = nullptr;
		com_ptr<ID3D10Blob> shaderBuffer = nullptr;
		com_ptr<ID3D11InputLayout> inputLoyoutDX11 = nullptr;
	};

	class PixelShaderDX11 : public PixelShader
	{
	public:
		explicit PixelShaderDX11() noexcept;
		PixelShaderDX11(const FPath& filePath);

		void Initialize(const FPath& filePath);
		virtual void Bind() noexcept override;

		ID3D11PixelShader* GetShader() const noexcept;
		ID3D10Blob* GetBuffer() const noexcept;

	private:
		com_ptr<ID3D11PixelShader> shader = nullptr;
		com_ptr<ID3D10Blob> shaderBuffer = nullptr;
	};
}