#pragma once
#include <string>
#include <vector>
#include "BindableDX11.hpp"

namespace LimeEngine
{
	enum class MaterialType;

	class VertexShaderDX11 : public BindableDX11
	{
	public:
		VertexShaderDX11(RenderingSystemDX11& renderingSystem) noexcept;
		VertexShaderDX11(RenderingSystemDX11& renderingSystem, std::wstring path, MaterialType materialType) noexcept;
		virtual ~VertexShaderDX11() override = default;

		void Initialize(std::wstring path, MaterialType materialType);
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
		PixelShaderDX11(RenderingSystemDX11& renderingSystem) noexcept;
		PixelShaderDX11(RenderingSystemDX11& renderingSystem, std::wstring path) noexcept;
		virtual ~PixelShaderDX11() override = default;

		void Initialize(std::wstring path);
		virtual void Bind() noexcept override;
		ID3D11PixelShader* GetShader() const noexcept;
		ID3D10Blob* GetBuffer() const noexcept;

	private:
		com_ptr<ID3D11PixelShader> shader = nullptr;
		com_ptr<ID3D10Blob> shaderBuffer = nullptr;
	};
}