// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "System.hpp"

namespace LimeEngine
{
	LE_DECLARE_EXTERN_LOGGER(LogSubsystem);

	class WorldSubsystemInitializer : public SubsystemInitializer
	{
	public:
		// World* world;
		std::string msg = "No msg :(";
	};

	class WorldSubsystemHolder : public SubsystemHolder
	{
	public:
		using Super = SubsystemHolder;
		using This = WorldSubsystemHolder;

		using SubsystemInitializerType = WorldSubsystemInitializer;

		void InstantiateSubsystems(const SubsystemInitializerType& Initializer)
		{
			InstantiateSubsystems(SubsystemManager::Get(), reinterpret_cast<const SubsystemInitializer&>(Initializer));
		}

	protected:
		virtual void InstantiateSubsystems(const SubsystemManager& subsystemManager, const SubsystemInitializer& Initializer) override
		{
			subsystemManager.InstantiateSubsystems<This>(*this, Initializer);
		}

	private:
		static void RegisterSubsystemHolder()
		{
			SubsystemManager& subsystemManager = SubsystemManager::Get();
			subsystemManager.RegisterSubsystemHolder<This>();
		}
		LE_STATIC_INITIALIZE(RegisterSubsystemHolder, SubsystemConstants::RegisterSubsystemHolderPriority);
	};

	class WorldSubsystem : public Subsystem
	{
	public:
		using Super = Subsystem;
		using This = WorldSubsystem;

		using SubsystemHolderType = WorldSubsystemHolder;

		explicit WorldSubsystem(const SubsystemInitializer& BaseInitializer) : This(reinterpret_cast<const SubsystemHolderType::SubsystemInitializerType&>(BaseInitializer)) {}
		explicit WorldSubsystem(const SubsystemHolderType::SubsystemInitializerType& Initializer) : Super(Initializer)
		{
			LE_LOG_DEBUG(LogDefault, Initializer.msg);
		}

		static URef<Subsystem> CreateSubsystem(const SubsystemInitializer& Initializer)
		{
			return std::make_unique<This>(Initializer);
		}

	private:
		static void RegisterSubsystem()
		{
			SubsystemManager& subsystemManager = SubsystemManager::Get();
			subsystemManager.RegisterSubsystem<SubsystemHolderType, This>();
		}
		LE_STATIC_INITIALIZE(RegisterSubsystem, SubsystemConstants::RegisterSubsystemPriority);
	};
}
