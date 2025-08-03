// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "System.hpp"

namespace LimeEngine
{
	class Application;

	class LE_API ApplicationSubsystemInitializer : public SubsystemInitializer
	{
	public:
		Application* application;
	};

	class LE_API ApplicationSubsystemHolder : public SubsystemHolder
	{
		LE_DEFINE_AND_REGISTER_SUBSYSTEM_HOLDER(ApplicationSubsystemHolder, ApplicationSubsystemInitializer);
	};

	class LE_API ApplicationSubsystem : public Subsystem
	{
		LE_DEFINE_AND_REGISTER_SUBSYSTEM(ApplicationSubsystem, ApplicationSubsystemHolder);

	public:
		using Super = Subsystem;

	public:
		explicit ApplicationSubsystem(const ApplicationSubsystemHolder::SubsystemInitializerType& Initializer) : Super(Initializer)
		{
			LE_LOG_DEBUG(LogSubsystem, "ApplicationSubsystem say hello!");
		}
	};
}
