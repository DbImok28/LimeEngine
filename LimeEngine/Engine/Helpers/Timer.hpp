#pragma once
#include <chrono>

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