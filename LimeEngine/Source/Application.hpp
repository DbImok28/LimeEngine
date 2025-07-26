// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Window/Console.hpp"

namespace LimeEngine
{
	class LE_API Application;
	URef<Application> CreateApplication();

	class LE_API Application
	{
		LE_DELETE_MOVE_COPY(Application)

	public:
		Application();
		virtual ~Application() = default;

		void Initialize();
		virtual void Run();

		Console* GetConsole() const;

	protected:
		bool autoRunConsole = true;
		URef<Console> console;
		URef<LoggerConsole> loggerConsole;
	};
}
