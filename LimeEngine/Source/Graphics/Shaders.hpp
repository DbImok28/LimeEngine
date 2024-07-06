// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "IBindable.hpp"

namespace LimeEngine
{
	enum class ShaderType
	{
		VertexShader,
		PixelShader
	};

	enum class ShaderDataType
	{
		R8,
		RG8,
		RGBA8,
		RGBA8_SRGB,

		R16F,
		RG16F,
		RGBA16F,

		R32F,
		RG32F,
		RGB32F,
		RGBA32F,

		RGB10A2,
		RGB10_XR_BIAS_A2,

		BGRA8,
		BGRA8_SRGB,

		R24G8,
		None
	};

	std::string ShaderDataTypeToString(ShaderDataType dataType) noexcept;

	class InputLayoutElement
	{
	public:
		InputLayoutElement() = default;
		InputLayoutElement(std::string name, ShaderDataType dataType, bool perVertex) : name(name), dataType(dataType), perVertex(perVertex) {}

		std::string name;
		ShaderDataType dataType = ShaderDataType::RGBA16F;
		bool perVertex = true;
	};

	class InputLayout
	{
	public:
		InputLayout() = default;
		InputLayout(std::initializer_list<InputLayoutElement> elements) : elements(elements) {}

		uint GetSize() const
		{
			return elements.size();
		}
		const std::vector<InputLayoutElement>& GetElements() const
		{
			return elements;
		}
		std::vector<InputLayoutElement>::iterator begin()
		{
			return elements.begin();
		}
		std::vector<InputLayoutElement>::iterator end()
		{
			return elements.end();
		}
		std::vector<InputLayoutElement>::const_iterator begin() const
		{
			return elements.begin();
		}
		std::vector<InputLayoutElement>::const_iterator end() const
		{
			return elements.end();
		}

	protected:
		std::vector<InputLayoutElement> elements;
	};

	class VertexShader : public IBindable
	{
	public:
		static URef<VertexShader> Create(const FPath& filePath, const InputLayout& inputLayout);

	public:
		virtual ~VertexShader() = default;

		const InputLayout& GetInputLayout() const noexcept
		{
			return inputLayout;
		}

	protected:
		InputLayout inputLayout;
	};

	class PixelShader : public IBindable
	{
	public:
		static URef<PixelShader> Create(const FPath& filePath);

	public:
		virtual ~PixelShader() = default;
	};

	class ShaderArray : public IBindable
	{
	public:
		ShaderArray() = default;
		ShaderArray(const InputLayout& inputLayout, const FPath& directoryPath, const std::string& name);

		void Load(const InputLayout& inputLayout, const FPath& directoryPath, const std::string& name);
		void Add(URef<IBindable>&& shader);
		virtual void Bind() override;

	private:
		std::vector<URef<IBindable>> shaders;
	};
}
