// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "System.hpp"

namespace LimeEngine
{
	class Scene;

	class LE_API WorldSubsystemInitializer : public SubsystemInitializer
	{
	public:
		Scene* scene;
	};

	class LE_API WorldSubsystemHolder : public SubsystemHolder
	{
		LE_DEFINE_AND_REGISTER_SUBSYSTEM_HOLDER(WorldSubsystemHolder, WorldSubsystemInitializer);
	};

	class LE_API WorldSubsystem : public Subsystem
	{
		LE_DEFINE_AND_REGISTER_SUBSYSTEM(WorldSubsystem, WorldSubsystemHolder);

	public:
		using Super = Subsystem;

	public:
		explicit WorldSubsystem(const WorldSubsystemHolder::SubsystemInitializerType& Initializer) : Super(Initializer)
		{
			LE_LOG_DEBUG(LogSubsystem, "WorldSubsystem say hello!");
		}
	};
}
