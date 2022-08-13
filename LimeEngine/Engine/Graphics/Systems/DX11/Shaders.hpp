#pragma once
#include <string>
#include <vector>
#include "BindableDX11.hpp"

namespace LimeEngine
{
	enum class MaterialType;

	class VertexShader : public BindableDX11
	{
	public:
		VertexShader(RenderingSystemDX11& renderingSystem) noexcept;
		virtual ~VertexShader() override = default;

		void Initalize(std::wstring shaderpath, MaterialType materialType);
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

	class PixelShader : public BindableDX11
	{
	public:
		PixelShader(RenderingSystemDX11& renderingSystem) noexcept;
		virtual ~PixelShader() override = default;

		void Initalize(std::wstring shaderpath);
		virtual void Bind() noexcept override;
		ID3D11PixelShader* GetShader() const noexcept;
		ID3D10Blob* GetBuffer() const noexcept;

	private:
		com_ptr<ID3D11PixelShader> shader = nullptr;
		com_ptr<ID3D10Blob> shaderBuffer = nullptr;
	};
}