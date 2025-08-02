// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine

#include "lepch.hpp"
#include "System.hpp"

namespace LimeEngine
{
	void SubsystemHolder::Reserve(uint32 capacity)
	{
		subsystems.reserve(subsystems.size() + capacity);
	}
	
	void SubsystemHolder::AddSubsystem(URef<Subsystem>&& subsystem)
	{
		subsystems.emplace_back(std::move(subsystem));
	}

	SubsystemManager SubsystemManager::instance;

	SubsystemManager& SubsystemManager::Get()
	{
		return instance;
	}

	void SubsystemManager::RegisterSubsystemHolderInternal(uint32 SubsystemHolderTypeIndex)
	{
		LE_ASSERT(subsystemRegistry.find(SubsystemHolderTypeIndex) == std::end(subsystemRegistry), "Subsystem holder is already registered");
		subsystemRegistry.emplace(SubsystemHolderTypeIndex, std::unordered_map<uint32, CreateSubsystemFunc>{});
	}

	void SubsystemManager::RegisterSubsystemInternal(uint32 SubsystemHolderTypeIndex, uint32 SubsystemTypeIndex, const SubsystemManager::CreateSubsystemFunc& CreateFunc)
	{
		auto subsystemsOfSubsystemHolder = subsystemRegistry.find(SubsystemTypeIndex);
		if (subsystemsOfSubsystemHolder == std::end(subsystemRegistry))
		{
			LE_ASSERT(false, "Subsystem holder is not registered");

			subsystemsOfSubsystemHolder = subsystemRegistry.emplace(SubsystemHolderTypeIndex, std::unordered_map<uint32, CreateSubsystemFunc>{}).first;
			LE_ASSERT(subsystemsOfSubsystemHolder != std::end(subsystemRegistry));
		}
		subsystemsOfSubsystemHolder->second.emplace(SubsystemHolderTypeIndex, CreateFunc);
	}

	void SubsystemManager::InstantiateSubsystemsInternal(SubsystemHolder& subsystemHolder, uint32 subsystemHolderTypeIndex, const SubsystemInitializer& Initializer) const
	{
		auto subsystemsOfSubsystemHolder = subsystemRegistry.find(subsystemHolderTypeIndex);
		if (subsystemsOfSubsystemHolder != std::end(subsystemRegistry))
		{
			subsystemHolder.Reserve(subsystemsOfSubsystemHolder->second.size());
			for (const auto& subsystemIt : subsystemsOfSubsystemHolder->second)
			{
				const CreateSubsystemFunc& CreateFunc = subsystemIt.second;
				subsystemHolder.AddSubsystem(CreateFunc(Initializer));
			}
		}
		else { LE_ASSERT(false, "Subsystem holder is not registered"); }
	}
}
