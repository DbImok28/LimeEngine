// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Material.hpp"

namespace LimeEngine
{
	MaterialParameters::MaterialParameters(std::vector<MaterialParameter>&& parameters) : parameters(std::move(parameters))
	{
		uint offset = 0u;
		for (auto& parameter : this->parameters)
		{
			parameter.offset = offset;
			offset += parameter.info->GetSize();
		}
	}

	void MaterialParameters::AddParameter(MaterialParameter&& parameter)
	{
		if (parameters.empty())
		{
			parameter.offset = 0u;
		}
		else
		{
			parameter.offset = parameters.back().offset + parameters.back().info->GetSize();
		}
		parameters.push_back(std::move(parameter));
	}

	MaterialParameterValues::MaterialParameterValues(const MaterialParameters& parameters) : parameters(parameters)
	{
		inputDataSize = parameters.back().offset + parameters.back().info->GetSize();
		inputData = MakeUnique<char[]>(inputDataSize);

		for (auto& parameter : parameters)
		{
			auto defaultValue = parameter.info->GetDefaultValue();
			SetParameter(defaultValue.second, defaultValue.first, parameter.offset);
		}
		isChanged = false;
		inputDataCB = ConstantBufferBase::Create(inputData.get(), inputDataSize);
	}

	void MaterialParameterValues::Bind()
	{
		if (isChanged)
		{
			inputDataCB->ApplyChanges(inputData.get(), inputDataSize);
			isChanged = false;
		}
		inputDataCB->Bind(ShaderType::VertexShader, 0u);
		inputDataCB->Bind(ShaderType::PixelShader, 0u);
	}

	std::vector<MaterialParameter>::const_iterator MaterialParameterValues::FindParameter(const std::string& name)
	{
		return std::find_if(std::cbegin(parameters), std::cend(parameters), [&name](const MaterialParameter& item) { return item.name == name; });
	}

	void MaterialParameterValues::SetParameter(void* value, uint valueSize, uint offset)
	{
		std::memcpy(&inputData.get()[offset], value, valueSize);
		isChanged = true;
	}

	void MaterialParameterValues::SetParameter(const std::string& name, void* value, uint valueSize)
	{
		auto parameterIter = FindParameter(name);
		if (parameterIter == std::cend(parameters))
		{
			LE_ASSERT(false, "Invalid material parameter name");
			return;
		}
		uint offset = parameterIter->offset;
		SetParameter(value, valueSize, offset);
	}

	void* MaterialParameterValues::GetParameter(uint offset)
	{
		return &inputData.get()[offset];
	}

	void* MaterialParameterValues::GetParameter(const std::string& name)
	{
		auto parameterIter = FindParameter(name);
		if (parameterIter == std::cend(parameters))
		{
			LE_ASSERT(false, "Invalid material parameter name");
			return nullptr;
		}
		uint offset = parameterIter->offset;
		return GetParameter(offset);
	}
}
