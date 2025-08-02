// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Base/Reflection.hpp"

namespace LimeEngine
{
	struct SubsystemConstants
	{
	public:
		static constexpr uint32_t RegisterSubsystemHolderPriority = 250u;
		static constexpr uint32_t EngineRegisterSubsystemPriority = 220u;
		static constexpr uint32_t RegisterSubsystemPriority = 200u;
	};

	class SubsystemInitializer
	{
	public:
		virtual ~SubsystemInitializer() = default;
	};

	class Subsystem
	{
	public:
		virtual ~Subsystem() = default;
		Subsystem(const SubsystemInitializer& Initializer) {};
	};

	class SubsystemManager;

	class SubsystemHolder
	{
	public:
		virtual ~SubsystemHolder() = default;

		void Reserve(uint32 capacity);
		void AddSubsystem(URef<Subsystem>&& subsystem);

	protected:
		virtual void InstantiateSubsystems(const SubsystemManager& subsystemManager, const SubsystemInitializer& Initializer) = 0;

	protected:
		std::vector<URef<Subsystem>> subsystems;
	};

	class SubsystemManager final
	{
	public:
		using CreateSubsystemFunc = std::function<URef<Subsystem>(const SubsystemInitializer&)>;

		template <std::derived_from<SubsystemHolder> TSubsystemHolder>
		void RegisterSubsystemHolder();

		template <std::derived_from<SubsystemHolder> TSubsystemHolder, std::derived_from<Subsystem> TSubsystem>
		void RegisterSubsystem();

		template <std::derived_from<SubsystemHolder> TSubsystemHolder>
		void InstantiateSubsystems(TSubsystemHolder& subsystemHolder, const SubsystemInitializer& Initializer) const;

		static SubsystemManager& Get();

	private:
		void RegisterSubsystemHolderInternal(uint32 SubsystemHolderTypeIndex);
		void RegisterSubsystemInternal(uint32 SubsystemHolderTypeIndex, uint32 SubsystemTypeIndex, const CreateSubsystemFunc& CreateFunc);
		void InstantiateSubsystemsInternal(SubsystemHolder& subsystemHolder, uint32 subsystemHolderTypeIndex, const SubsystemInitializer& Initializer) const;

	private:
		uint32 subsystemTypeIndexCounter = 0u;
		uint32 subsystemHolderTypeIndexCounter = 0u;

		std::unordered_map<uint32, std::unordered_map<uint32, CreateSubsystemFunc>> subsystemRegistry;

		static SubsystemManager instance;
	};

	template <std::derived_from<SubsystemHolder> TSubsystemHolder>
	void SubsystemManager::RegisterSubsystemHolder()
	{
		if (TypeIndex<TSubsystemHolder>::index == 0u) { TypeIndex<TSubsystemHolder>::index = ++subsystemHolderTypeIndexCounter; }
		else { LE_ASSERT(false, "Subsystem holder is already registered"); }
		RegisterSubsystemHolderInternal(TypeIndex<TSubsystemHolder>::index);
	}

	template <std::derived_from<SubsystemHolder> TSubsystemHolder, std::derived_from<Subsystem> TSubsystem>
	void SubsystemManager::RegisterSubsystem()
	{
		if (TypeIndex<TSubsystem>::index == 0u) { TypeIndex<TSubsystem>::index = ++subsystemTypeIndexCounter; }
		else { LE_ASSERT(false, "Subsystem is already registered"); }

		if (TypeIndex<TSubsystemHolder>::index == 0u)
		{
			LE_ASSERT(false, "Subsystem holder is not registered");
			RegisterSubsystemHolder<TSubsystemHolder>();
		}
		RegisterSubsystemInternal(TypeIndex<TSubsystemHolder>::index, TypeIndex<TSubsystem>::index, TSubsystem::CreateSubsystem);
	}

	template <std::derived_from<SubsystemHolder> TSubsystemHolder>
	void SubsystemManager::InstantiateSubsystems(TSubsystemHolder& subsystemHolder, const SubsystemInitializer& Initializer) const
	{
		InstantiateSubsystemsInternal(subsystemHolder, TypeIndex<TSubsystemHolder>::index, Initializer);
	}
}
