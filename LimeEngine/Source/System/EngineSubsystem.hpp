// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "System.hpp"

namespace LimeEngine
{
	class Engine;

	class LE_API EngineSubsystemInitializer : public SubsystemInitializer
	{
	public:
		Engine* engine;
	};

	class LE_API EngineSubsystemHolder : public SubsystemHolder
	{
		LE_DEFINE_AND_REGISTER_SUBSYSTEM_HOLDER(EngineSubsystemHolder, EngineSubsystemInitializer);
	};

	class LE_API EngineSubsystem : public Subsystem
	{
		LE_DEFINE_AND_REGISTER_SUBSYSTEM(EngineSubsystem, EngineSubsystemHolder);

	public:
		using Super = Subsystem;

	public:
		explicit EngineSubsystem(const EngineSubsystemHolder::SubsystemInitializerType& Initializer) : Super(Initializer)
		{
			LE_LOG_DEBUG(LogSubsystem, "EngineSubsystem say hello!");
		}
	};
}
