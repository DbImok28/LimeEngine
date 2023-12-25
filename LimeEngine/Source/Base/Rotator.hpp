// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include <DirectXMath.h>
#include "Vector.hpp"

namespace LimeEngine
{
	using TempQuaternion = DirectX::XMVECTOR;

	class Rotator
	{
	public:
		Rotator() noexcept;
		Rotator(float rollDeg, float pitchDeg, float yawDeg) noexcept;
		Rotator(const Rotator& other) noexcept = default;
		Rotator(Rotator&& other) noexcept = default;
		Rotator& operator=(const Rotator& other) noexcept = default;
		Rotator& operator=(Rotator&& other) noexcept = default;

		static Rotator MakeFromRadians(float rollRad, float pitchRad, float yawRad) noexcept;
		static Rotator MakeRotator(TempQuaternion q) noexcept;
		static TempQuaternion MakeTempQuaternion(const Rotator& rot) noexcept;
		static TempQuaternion MakeTempQuaternion(float roll, float pitch, float yaw) noexcept;
		static TempQuaternion MakeTempQuaternionFromRadians(const Rotator& rot) noexcept;
		static TempQuaternion MakeTempQuaternionFromRadians(float roll, float pitch, float yaw) noexcept;

		bool operator==(const Rotator& other) const noexcept;
		bool operator!=(const Rotator& other) const noexcept;

		void Combine(const Rotator& other) noexcept;

		TempQuaternion GetQuaternion() const noexcept;
		void SetQuaternion(TempQuaternion quat) noexcept;
		TempVector GetEuler() const noexcept;
		void SetEuler(TempVector euler) noexcept;
		float* GetArray() noexcept;
		std::string ToString() const noexcept;

	public:
		union
		{
			struct
			{
				float roll;  // x deg
				float pitch; // y deg
				float yaw;   // z deg
			};
			DirectX::XMFLOAT3 vec3{};
		};
	};

	std::ostream& operator<<(std::ostream& os, const Rotator& rot);

}

template <>
struct std::formatter<LimeEngine::Rotator> : std::formatter<std::string>
{
	auto format(LimeEngine::Rotator rot, auto& ctx) const
	{
		return std::format_to(ctx.out(), "x:{:< 8} y:{:< 8} z:{:< 8}", rot.roll, rot.pitch, rot.yaw);
	}
};
