// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

namespace LimeEngine
{
	class LE_API Application;
	std::unique_ptr<Application> CreateApplication();

	class LE_API Application
	{
		Application(const Application&) = delete;
		Application(Application&&) noexcept = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) noexcept = delete;

	public:
		Application() = default;
		virtual ~Application() = default;
		void Run();
	};
}
