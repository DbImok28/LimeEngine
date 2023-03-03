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
}