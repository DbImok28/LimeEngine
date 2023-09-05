// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

namespace LimeEngine
{
	class Timer
	{
	public:
		Timer() noexcept;
		float ElapsedTime() const noexcept;
		bool IsRunning() const noexcept;
		bool Stop() noexcept;
		bool Start() noexcept;
		void Restart() noexcept;

	private:
		bool isRunning = false;
		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> stop;
	};
}