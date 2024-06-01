// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Texture2D.hpp"
#include "Base/GameResource.hpp"
#include "Shaders.hpp"
#include "Buffers.hpp"

namespace LimeEngine
{
	enum class MaterialParameterType
	{
		Float,
		Float2,
		Float3,
		Float4,
		Texture
	};

	class MaterialParameterInfoBase
	{
	public:
		virtual std::pair<uint, char*> GetDefaultValue() = 0;
		virtual uint GetSize() = 0;
	};

	template <typename T>
	class MaterialParameterInfo : public MaterialParameterInfoBase
	{
	public:
		MaterialParameterInfo(T defaultValue) : defaultValue(defaultValue) {}

		virtual std::pair<uint, char*> GetDefaultValue() override
		{
			return std::make_pair(sizeof(T), reinterpret_cast<char*>(&defaultValue));
		}
		virtual uint GetSize() override
		{
			return sizeof(T);
		}

	private:
		T defaultValue;
	};

	class MaterialParameter
	{
	public:
		template <typename T>
		MaterialParameter(std::string name, T defaultValue, uint offset) : name(name), offset(offset), info(std::make_unique<MaterialParameterInfo<T>>(defaultValue))
		{}
		template <typename T>
		MaterialParameter(std::string name, T defaultValue) : name(name), info(std::make_unique<MaterialParameterInfo<T>>(defaultValue))
		{}

		std::string name;
		std::unique_ptr<MaterialParameterInfoBase> info;
		uint offset = 0u;
	};

	class MaterialParameters
	{
	public:
		MaterialParameters() = default;
		MaterialParameters(std::vector<MaterialParameter>&& parameters);

		void AddParameter(MaterialParameter&& parameter);
		template <typename T>
		void AddParameter(std::string name, T defaultValue)
		{
			uint offset = 0u;
			if (!parameters.empty())
			{
				offset = parameters.back().offset + parameters.back().info->GetSize();
			}
			parameters.emplace_back(name, defaultValue, offset);
		}

		uint GetSize() const
		{
			return parameters.size();
		}
		const std::vector<MaterialParameter>& GetElements() const
		{
			return parameters;
		}
		std::vector<MaterialParameter>::iterator begin()
		{
			return parameters.begin();
		}
		std::vector<MaterialParameter>::iterator end()
		{
			return parameters.end();
		}
		std::vector<MaterialParameter>::const_iterator begin() const
		{
			return parameters.begin();
		}
		std::vector<MaterialParameter>::const_iterator end() const
		{
			return parameters.end();
		}
		const MaterialParameter& back() const
		{
			return parameters.back();
		}

	public:
		std::vector<MaterialParameter> parameters;
	};

	class MaterialParameterValues
	{
	public:
		MaterialParameterValues(const MaterialParameters& parameters);

		void Bind();

		template <typename T>
		void SetParameter(const std::string& name, T value)
		{
			SetParameter(name, &value, sizeof(T));
		}

		template <typename T>
		T GetParameter(const std::string& name)
		{
			return *reinterpret_cast<T*>(GetParameter(name));
		}

	private:
		std::vector<MaterialParameter>::const_iterator FindParameter(const std::string& name);

		void SetParameter(void* value, uint valueSize, uint offset);
		void SetParameter(const std::string& name, void* value, uint valueSize);
		void* GetParameter(uint offset);
		void* GetParameter(const std::string& name);

	private:
		std::unique_ptr<char[]> inputData;
		std::unique_ptr<ConstantBufferBase> inputDataCB;
		const MaterialParameters& parameters;
		uint inputDataSize;
		bool isChanged = false;
	};
}
