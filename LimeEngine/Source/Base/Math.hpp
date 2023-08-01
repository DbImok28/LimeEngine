// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include <cmath>
#include <DirectXMath.h>

namespace LimeEngine
{
	class Math
	{
	public:
		static constexpr float pi = 3.141592653f;
		static constexpr float pi2 = 6.283185307f;
		static constexpr float div1ByPi = 0.318309886f;
		static constexpr float div1By2Pi = 0.159154943f;
		static constexpr float piDivBy2 = 1.570796327f;
		static constexpr float piDivBy4 = 0.785398163f;

		static constexpr float toRadians = pi / 180.0f;
		static constexpr float toDegress = 180.0f / pi;

		static inline constexpr float ConvertToDegrees(float radians) noexcept
		{
			return radians * toDegress;
		}
		static inline constexpr float ConvertToRadians(float degrees) noexcept
		{
			return degrees * toRadians;
		}

		static inline float Sin(float x) noexcept
		{
			return std::sinf(x);
		}
		static inline float ASin(float x) noexcept
		{
			return std::asinf(x);
		}
		static inline float Cos(float x) noexcept
		{
			return std::cosf(x);
		}
		static inline float ACos(float x) noexcept
		{
			return std::acosf(x);
		}
		static inline float Tan(float x) noexcept
		{
			return std::tanf(x);
		}
		static inline float ATan(float x) noexcept
		{
			return std::atanf(x);
		}
		static inline float ATan2(float y, float x) noexcept
		{
			return std::atan2f(y, x);
		}

		static inline float Abs(float x) noexcept
		{
			return std::fabs(x);
		}
		static inline float Round(float x) noexcept
		{
			return std::roundf(x);
		}
		static inline float Floor(float x) noexcept
		{
			return std::floorf(x);
		}
		static inline float Ceil(float x) noexcept
		{
			return std::ceilf(x);
		}
		static inline float Trunc(float x) noexcept
		{
			return std::truncf(x);
		}

		static inline float Sqrt(float x) noexcept
		{
			return std::sqrtf(x);
		}
		static inline float Pow(float x, float n) noexcept
		{
			return std::powf(x, n);
		}
		static inline float Root(float x, float n) noexcept
		{
			return std::powf(x, 1.0f / n);
		}
		static inline float Copysign(float num, float sign) noexcept
		{
			return std::copysignf(num, sign);
		}
		static inline constexpr float FlipUV(float u) noexcept
		{
			return -u + 1.0f;
		}
		static inline bool IsNearEqual(float x1, float x2, float tolerance = std::numeric_limits<float>::epsilon()) noexcept
		{
			return Abs(x1 - x2) <= tolerance;
		}
	};
}
