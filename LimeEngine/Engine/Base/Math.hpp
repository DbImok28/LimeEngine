#pragma once
#include <cmath>
#include <DirectXMath.h>

namespace LimeEngine
{
	class Math
	{
	public:
		static constexpr float pi = 3.141592653f;
		static constexpr float toRad = pi / 180.0f;
		static float Sin(float x) noexcept
		{
			return std::sinf(x);
		}
		static float Cos(float x) noexcept
		{
			return std::cosf(x);
		}
		static float Tan(float x) noexcept
		{
			return std::tanf(x);
		}
		static float Sqrt(float x) noexcept
		{
			return std::sqrtf(x);
		}
		static float Pow(float x, float n) noexcept
		{
			return std::powf(x, n);
		}
		static float Root(float x, float n) noexcept
		{
			return std::powf(x, 1.0f / n);
		}
		static float FlipUV(float u) noexcept
		{
			return -u + 1.0f;
		}
	};
}
