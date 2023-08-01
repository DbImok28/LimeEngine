// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

namespace LimeEngine
{
	class LE_API Application;
	std::unique_ptr<Application> CreateApplication();

	class LE_API Application
	{
		LE_DELETE_MOVE_COPY(Application)

	public:
		Application() = default;
		virtual ~Application() = default;
		void Run();
	};
}
